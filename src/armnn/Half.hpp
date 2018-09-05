//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <type_traits>
#include <half/half.hpp>

namespace armnn
{
    using Half = half_float::half; //import half float implementation
} //namespace armnn


namespace std
{

template<>
struct is_floating_point<armnn::Half>
    : integral_constant< bool, true >
{};

template<>
struct is_floating_point<const armnn::Half>
    : integral_constant< bool, true >
{};

template<>
struct is_floating_point<volatile armnn::Half>
    : integral_constant< bool, true >
{};

} //namespace std