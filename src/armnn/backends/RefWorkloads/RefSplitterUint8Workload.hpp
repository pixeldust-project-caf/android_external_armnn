﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "backends/Workload.hpp"
#include "backends/WorkloadData.hpp"

namespace armnn
{

class RefSplitterUint8Workload : public Uint8Workload<SplitterQueueDescriptor>
{
public:
    using Uint8Workload<SplitterQueueDescriptor>::Uint8Workload;
    virtual void Execute() const override;
};

} //namespace armnn
