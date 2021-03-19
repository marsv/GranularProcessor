/*
  ==============================================================================

    ClampedInt.h
    Created: 19 Mar 2021 17:41:57pm
    Author:  Johannes Elliesen

  ==============================================================================
*/

#pragma once

#include <stdint.h>
#include "MathFunctions.h"

#ifndef _INLINE_
#    define _INLINE_ inline
#endif

template <int min, int max, typename IntType = int32_t>
class ClampedInt
{
public:
    template <typename OtherIntType>
    _INLINE_ constexpr ClampedInt(OtherIntType initialValue = OtherIntType(0))
    {
        value_ = MathFunctions::limit(initialValue, min, max);
    }

    _INLINE_ constexpr ClampedInt(const ClampedInt& other)
    {
        value_ = other.value_;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr operator OtherIntType() const
    {
        return OtherIntType(value_);
    }

    _INLINE_ constexpr const ClampedInt& operator=(const ClampedInt& other)
    {
        value_ = other.value_;
        return *this;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr const ClampedInt& operator=(const OtherIntType rhs)
    {
        value_ = MathFunctions::limit(IntType(rhs), min, max);
        return *this;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr const ClampedInt& operator+=(const OtherIntType rhs)
    {
        value_ = MathFunctions::limit(IntType(OtherIntType(value_) + rhs), min, max);
        return *this;
    }

    template <typename OtherIntType>
    _INLINE_ constexpr const ClampedInt& operator-=(const OtherIntType rhs)
    {
        value_ = MathFunctions::limit(IntType(OtherIntType(value_) - rhs), min, max);
        return *this;
    }

    _INLINE_ constexpr const ClampedInt& operator++(int)
    {
        value_++;
        if (value_ > max)
            value_ = max;
        return *this;
    }

    _INLINE_ constexpr const ClampedInt& operator--(int)
    {
        value_--;
        if (value_ < min)
            value_ = min;
        return *this;
    }

private:
    IntType value_;
};

template <int min, int max, typename IntType, typename OtherIntType>
_INLINE_ constexpr ClampedInt<min, max, IntType> operator+(OtherIntType lhs, const ClampedInt<min, max, IntType>& rhs)
{
    return ClampedInt<min, max, IntType>(lhs + OtherIntType(rhs));
}

template <int min, int max, typename IntType, typename OtherIntType>
_INLINE_ constexpr ClampedInt<min, max, IntType> operator+(const ClampedInt<min, max, IntType>& lhs, OtherIntType rhs)
{
    return ClampedInt<min, max, IntType>(OtherIntType(lhs) + rhs);
}

template <int min, int max, typename IntType, typename OtherIntType>
_INLINE_ constexpr ClampedInt<min, max, IntType> operator-(OtherIntType lhs, const ClampedInt<min, max, IntType>& rhs)
{
    return ClampedInt<min, max, IntType>(lhs - OtherIntType(rhs));
}

template <int min, int max, typename IntType, typename OtherIntType>
_INLINE_ constexpr ClampedInt<min, max, IntType> operator-(const ClampedInt<min, max, IntType>& lhs, OtherIntType rhs)
{
    return ClampedInt<min, max, IntType>(OtherIntType(lhs) - rhs);
}