﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "backends/Workload.hpp"
#include "backends/WorkloadData.hpp"

namespace armnn
{

class RefReshapeUint8Workload : public Uint8Workload<ReshapeQueueDescriptor>
{
public:
    using Uint8Workload<ReshapeQueueDescriptor>::Uint8Workload;
    virtual void Execute() const override;
};

} //namespace armnn
