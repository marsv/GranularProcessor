/*
  ==============================================================================

    MathFunctions.h
    Created: 19 Mar 2021 12:31:57pm
    Author:  Johannes Elliesen

  ==============================================================================
*/

#pragma once

#ifndef _INLINE_
#    define _INLINE_ inline
#endif

namespace MathFunctions
{
    template <typename Type>
    _INLINE_ constexpr Type linMap(Type relativeValue, Type min, Type max)
    {
        return min + relativeValue * (max - min);
    }

    template <typename Type>
    _INLINE_ constexpr Type limit(Type value, Type min, Type max)
    {
        return value < min ? min : (max < value ? max : value);
    }

    template <typename Type>
    _INLINE_ constexpr Type min(Type a, Type b)
    {
        return a < b ? a : b;
    }

    template <typename Type>
    _INLINE_ constexpr Type max(Type a, Type b)
    {
        return a > b ? a : b;
    }

    template <typename Type>
    _INLINE_ static Type wrap(Type x, Type max)
    {
        while (x > max)
            x -= max;
        while (x < 0)
            x += max;
        return x;
    }
}
