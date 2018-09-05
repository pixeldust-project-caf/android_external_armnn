﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#pragma once

namespace armnn
{

class TensorShape;

class ITensorHandle
{
public:
    enum Type
    {
        Cpu,
        CL,
        Neon
    };

    virtual ~ITensorHandle(){}

    /// Indicate to the memory manager that this resource is active.
    /// This is used to compute overlapping lifetimes of resources.
    virtual void Manage() = 0;

    /// Indicate to the memory manager that this resource is no longer active.
    /// This is used to compute overlapping lifetimes of resources.
    virtual void Allocate() = 0;

    /// Get the type backend associated with the tensor handle.
    /// \return Type enum
    virtual ITensorHandle::Type GetType() const = 0;

    /// Get the parent tensor if this is a subtensor.
    /// \return a pointer to the parent tensor. Otherwise nullptr if not a subtensor.
    virtual ITensorHandle* GetParent() const = 0;

    /// Map the tensor data for access.
    /// \param blocking hint to block the calling thread until all other accesses are complete. (backend dependent)
    /// \return pointer to the first element of the mapped data.
    virtual const void* Map(bool blocking=true) const = 0;

    /// Unmap the tensor data
    virtual void Unmap() const = 0;

    /// Map the tensor data for access. Must be paired with call to Unmap().
    /// \param blocking hint to block the calling thread until all other accesses are complete. (backend dependent)
    /// \return pointer to the first element of the mapped data.
    void* Map(bool blocking=true)
    {
        return const_cast<void*>(static_cast<const ITensorHandle*>(this)->Map(blocking));
    }

    /// Unmap the tensor data that was previously mapped with call to Map().
    void Unmap()
    {
        return static_cast<const ITensorHandle*>(this)->Unmap();
    }

    /// Get the strides for each dimension ordered from largest to smallest where
    /// the smallest value is the same as the size of a single element in the tensor.
    /// \return a TensorShape filled with the strides for each dimension
    virtual TensorShape GetStrides() const = 0;

    /// Get the number of elements for each dimension orderd from slowest iterating dimension
    /// to fastest iterating dimension.
    /// \return a TensorShape filled with the number of elements for each dimension.
    virtual TensorShape GetShape() const = 0;
};

}
