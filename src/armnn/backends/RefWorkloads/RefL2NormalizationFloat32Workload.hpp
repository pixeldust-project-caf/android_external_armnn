﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "backends/Workload.hpp"
#include "backends/WorkloadData.hpp"

namespace armnn
{

class RefL2NormalizationFloat32Workload : public Float32Workload<L2NormalizationQueueDescriptor>
{
public:
    using Float32Workload<L2NormalizationQueueDescriptor>::Float32Workload;
    virtual void Execute() const override;
};

} //namespace armnn
