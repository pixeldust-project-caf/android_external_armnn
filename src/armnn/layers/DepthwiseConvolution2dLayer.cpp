//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#include "DepthwiseConvolution2dLayer.hpp"

#include "LayerCloneBase.hpp"

#include <armnn/TypesUtils.hpp>
#include <backends/CpuTensorHandle.hpp>
#include <backends/WorkloadFactory.hpp>

namespace armnn
{

DepthwiseConvolution2dLayer::DepthwiseConvolution2dLayer(const DepthwiseConvolution2dDescriptor& param,
                                                         const char* name)
    : LayerWithParameters(1, 1, LayerType::DepthwiseConvolution2d, param, name)
{
}

std::unique_ptr<IWorkload> DepthwiseConvolution2dLayer::CreateWorkload(const Graph&                  graph,
                                                                       const IWorkloadFactory& factory) const
{
    // on this level constant data should not be released..
    BOOST_ASSERT_MSG(m_Weight != nullptr, "DepthwiseConvolution2dLayer: Weights data should not be null.");

    DepthwiseConvolution2dQueueDescriptor descriptor;

    descriptor.m_Weight = m_Weight.get();
    if (m_Param.m_BiasEnabled)
    {
        BOOST_ASSERT_MSG(m_Bias != nullptr, "DepthwiseConvolution2dLayer: Bias data should not be null.");
        descriptor.m_Bias = m_Bias.get();
    }
    return factory.CreateDepthwiseConvolution2d(descriptor, PrepInfoAndDesc(descriptor, graph));
}

DepthwiseConvolution2dLayer* DepthwiseConvolution2dLayer::Clone(Graph& graph) const
{
    auto layer      = CloneBase<DepthwiseConvolution2dLayer>(graph, m_Param, GetName());
    layer->m_Weight = m_Weight ? std::make_unique<ScopedCpuTensorHandle>(*m_Weight) : nullptr;

    if (layer->m_Param.m_BiasEnabled)
    {
        layer->m_Bias = m_Bias ? std::make_unique<ScopedCpuTensorHandle>(*m_Bias) : nullptr;
    }

    return std::move(layer);
}

std::vector<TensorShape>
DepthwiseConvolution2dLayer::InferOutputShapes(const std::vector<TensorShape>& inputShapes) const
{
    BOOST_ASSERT(inputShapes.size() == 2);
    const TensorShape& inputShape = inputShapes[0];
    const TensorShape filterShape = inputShapes[1];

    BOOST_ASSERT_MSG(inputShape.GetNumDimensions() == 4, "Convolutions will always have 4D input.");

    unsigned int inWidth = inputShape[3];
    unsigned int inHeight = inputShape[2];
    unsigned int inBatchSize = inputShape[0];

    unsigned int filterWidth = filterShape[3];
    unsigned int readWidth = (inWidth + m_Param.m_PadLeft + m_Param.m_PadRight) - (filterWidth);
    unsigned int outWidth =  1+(readWidth / m_Param.m_StrideX);

    unsigned int filterHeight = filterShape[2];
    unsigned int readHeight = (inHeight + m_Param.m_PadTop + m_Param.m_PadBottom) - (filterHeight);
    unsigned int outHeight = 1+(readHeight / m_Param.m_StrideY);
    unsigned int depthMultiplier = filterShape[0];

    unsigned int outChannels = filterShape[1]*depthMultiplier;
    unsigned int outBatchSize = inBatchSize;

    return std::vector<TensorShape>({ TensorShape({outBatchSize, outChannels, outHeight, outWidth})});
}

void DepthwiseConvolution2dLayer::ValidateTensorShapesFromInputs()
{
    VerifyLayerConnections(1, CHECK_LOCATION());

    // on this level constant data should not be released..
    BOOST_ASSERT_MSG(m_Weight != nullptr, "DepthwiseConvolution2dLayer: Weights data should not be null.");

    auto inferredShapes = InferOutputShapes({
        GetInputSlot(0).GetConnection()->GetTensorInfo().GetShape(),
        m_Weight->GetTensorInfo().GetShape()
     });

    BOOST_ASSERT(inferredShapes.size() == 1);

    ConditionalThrowIfNotEqual<LayerValidationException>(
        "DepthwiseConvolution2dLayer: TensorShape set on OutputSlot[0] does not match the inferred shape.",
        GetOutputSlot(0).GetTensorInfo().GetShape(),
        inferredShapes[0]);
}

Layer::ConstantTensors DepthwiseConvolution2dLayer::GetConstantTensorsByRef()
{
    return {m_Weight, m_Bias};
}

} // namespace armnn
