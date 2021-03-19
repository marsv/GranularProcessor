/*
  ==============================================================================

    ExponentialSmoother.h
    Created: 19 Mar 2021 12:31:57pm
    Author:  Johannes Elliesen

  ==============================================================================
*/

#pragma once

#include "util/StrongTypes.h"
#include <cmath>
#include "gcem.hpp"

#ifndef _INLINE_
#    define _INLINE_ inline
#endif

class ExponentialSmoother
{
public:
    /** Time constant that defines the smoothing time of an ExponentialSmoother. */
    class TimeConstant
    {
    public:
        using RiseTime = StrongTypes::NamedArgument<StrongTypes::TimeValue<float>, struct SmoothingTimeTag>;
        using SampleRate = StrongTypes::NamedArgument<StrongTypes::FrequencyValue<float>, struct SampleRateTag>;

        /**
         *  @param sampleRate   The sample rate with which getNextValue() will be called.
         *  @param riseTime     The time the signal takes to reach 88.8% of the target value 
         *                      (or: The time between reaching 10% and 90% of the target value)
         */
        constexpr TimeConstant(SampleRate sampleRate, RiseTime riseTime) :
            tau_(1.0f - gcem::exp(-2.2f / sampleRate.get().getHz() / riseTime.get().getSeconds()))
        {
            // see: Zoelzer, Digital Audio Signal Processing, 2nd Ed., 7.2.3 Time Constants
        }

        constexpr TimeConstant(const TimeConstant& other) :
            tau_(other.tau_)
        {
        }

        constexpr operator float() const { return tau_; }

    private:
        float tau_;
    };

    ExponentialSmoother() :
        lastVal_(0.0f)
    {
    }

    /** Returns the current value */
    float getCurrentValue() const { return lastVal_; }

    /** Advances the smoother by one sample and returns the new value. 
     *  timeConstant may be a constexpr in case the samplerate and rise time are fixed.
     */
    _INLINE_ float getNextValue(float targetVal, const TimeConstant& timeConstant)
    {
        lastVal_ = (targetVal - lastVal_) * timeConstant + lastVal_;
        return lastVal_;
    }

    /** Resets the smoother to a known value. */
    void reset(float valueToResetTo = 0.0f)
    {
        lastVal_ = valueToResetTo;
    }

private:
    float lastVal_;
};
