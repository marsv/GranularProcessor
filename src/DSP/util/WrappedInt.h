/*
  ==============================================================================

    WrappedInt.h
    Created: 19 Mar 2021 12:31:57pm
    Author:  Johannes Elliesen

  ==============================================================================
*/

#pragma once

#include <stdint.h>

#ifndef _INLINE_
#    define _INLINE_ inline
#endif

template <int size, typename IntType = int32_t>
class WrappedInt
{
public:
    template <typename OtherIntType>
    _INLINE_ constexpr WrappedInt(OtherIntType initialValue = OtherIntType(0))
    {
        value_ = getWrapped(initialValue);
    }

    _INLINE_ constexpr WrappedInt(const WrappedInt& other)
    {
        value_ = other.value_;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr operator OtherIntType() const
    {
        return OtherIntType(value_);
    }

    _INLINE_ constexpr const WrappedInt& operator=(const WrappedInt& other)
    {
        value_ = other.value_;
        return *this;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr const WrappedInt& operator=(const OtherIntType rhs)
    {
        value_ = getWrapped(IntType(rhs));
        return *this;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr const WrappedInt& operator+=(const OtherIntType rhs)
    {
        value_ = getWrapped(IntType(OtherIntType(value_) + rhs));
        return *this;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr const WrappedInt& operator-=(const OtherIntType rhs)
    {
        value_ = getWrapped(OtherIntType(value_) - rhs);
        return *this;
    }

    _INLINE_ constexpr const WrappedInt& operator++(int)
    {
        value_++;
        if (value_ >= size)
            value_ = 0;
        return *this;
    }

private:
    template <typename OtherIntType>
    _INLINE_ constexpr IntType getWrapped(OtherIntType in)
    {
        while (in < 0)
            in += size;
        while (in >= size)
            in -= size;
        return in;
    }
    IntType value_;
};

template <int size, typename IntType, typename OtherIntType>
_INLINE_ constexpr WrappedInt<size, IntType> operator+(OtherIntType lhs, const WrappedInt<size, IntType>& rhs)
{
    return WrappedInt<size, IntType>(lhs + OtherIntType(rhs));
}

template <int size, typename IntType, typename OtherIntType>
_INLINE_ constexpr WrappedInt<size, IntType> operator+(const WrappedInt<size, IntType>& lhs, OtherIntType rhs)
{
    return WrappedInt<size, IntType>(OtherIntType(lhs) + rhs);
}

template <int size, typename IntType, typename OtherIntType>
_INLINE_ constexpr WrappedInt<size, IntType> operator-(OtherIntType lhs, const WrappedInt<size, IntType>& rhs)
{
    return WrappedInt<size, IntType>(lhs - OtherIntType(rhs));
}

template <int size, typename IntType, typename OtherIntType>
_INLINE_ constexpr WrappedInt<size, IntType> operator-(const WrappedInt<size, IntType>& lhs, OtherIntType rhs)
{
    return WrappedInt<size, IntType>(OtherIntType(lhs) - rhs);
}
