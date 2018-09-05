//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <backends/NeonWorkloadUtils.hpp>

namespace armnn
{

class NeonDepthwiseConvolutionFloatWorkload : public FloatWorkload<DepthwiseConvolution2dQueueDescriptor>
{
public:
    NeonDepthwiseConvolutionFloatWorkload(const DepthwiseConvolution2dQueueDescriptor& descriptor,
                                          const WorkloadInfo& info);
    virtual void Execute() const override;

private:
    mutable std::unique_ptr<arm_compute::IFunction> m_pDepthwiseConvolutionLayer;

    std::unique_ptr<arm_compute::Tensor> m_KernelTensor;
    std::unique_ptr<arm_compute::Tensor> m_BiasTensor;

    void FreeUnusedTensors();
};

} //namespace armnn




