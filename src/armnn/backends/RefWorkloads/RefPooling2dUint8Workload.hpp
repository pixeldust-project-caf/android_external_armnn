﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "backends/Workload.hpp"
#include "backends/WorkloadData.hpp"

namespace armnn
{

class RefPooling2dUint8Workload : public Uint8Workload<Pooling2dQueueDescriptor>
{
public:
    using Uint8Workload<Pooling2dQueueDescriptor>::Uint8Workload;
    virtual void Execute() const override;
};

} //namespace armnn
