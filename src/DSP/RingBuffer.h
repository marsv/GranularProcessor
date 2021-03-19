#pragma once

#include "JuceHeader.h"
#include <juce_dsp/juce_dsp.h>
#include "util/ClampedInt.h"
#include "util/WrappedInt.h"
#include "util/MathFunctions.h"

#ifndef _INLINE_
#    define _INLINE_ inline
#endif

//======================================================================================

//======================================================================================

template <typename FloatType, size_t numChannels, size_t numSamples>
class FixedSizeRingBuffer
{
public:
    using Type = FloatType;
    using ChannelIdx = ClampedInt<0, numChannels, size_t>;
    using SampleIdx = WrappedInt<numSamples>;

    constexpr FixedSizeRingBuffer()
    {
    }

    _INLINE_ constexpr FloatType& at(ChannelIdx ch, SampleIdx sample) { return buffer_[ch][sample]; }
    _INLINE_ constexpr const FloatType& at(ChannelIdx ch, SampleIdx sample) const { return buffer_[ch][sample]; }

    constexpr void fill(FloatType value)
    {
    
    }

    _INLINE_ constexpr size_t getNumChannels() const { return numChannels; }
    _INLINE_ constexpr size_t getNumSamples() const { return numSamples; }

    _INLINE_ SampleIdx getWriteIdx() const { return writeIdx_; }
    _INLINE_ void advanceWriteIdx() { writeIdx_++; }

    void writeBlock(juce::dsp::AudioBlock<FloatType> block)
    {
        jassert(block.getNumChannels() == numChannels);
        jassert(block.getNumSamples() <= numSamples);

        const auto numChannelsToCopy = std::min(block.getNumChannels(), numChannels);
        const auto numSamplesToCopy = block.getNumSamples();
        for (size_t i = 0; i < numSamplesToCopy; i++)
        {
            for (size_t ch = 0; ch < numChannelsToCopy; ch++)
                buffer_[ch][writeIdx_] = block.getSample(ch, i);
            writeIdx_++;
        }
    }

private:
    FloatType buffer_[numChannels][numSamples];
    SampleIdx writeIdx_;
};

//======================================================================================

//======================================================================================

template <typename FloatType>
class VariableSizeRingBuffer
{
public:
    using Type = FloatType;

    constexpr VariableSizeRingBuffer() :
        writeIdx_(0),
        numChannels_(0),
        numSamples_(0)
    {
    }

    void resize(size_t numChannels, size_t numSamples)
    {
        buffer_ = juce::dsp::AudioBlock<FloatType>(storage_, numChannels, numSamples);
        writeIdx_ = 0;
    }

    _INLINE_ constexpr const FloatType& at(size_t ch, size_t sample) const { return at(ch, sample); }
    _INLINE_ constexpr FloatType& at(size_t ch, size_t sample) 
    { 
        ch = MathFunctions::min(ch, numChannels_);
        sample = MathFunctions::wrap(sample, numSamples_);
        return buffer_[ch][sample];
    }

    _INLINE_ constexpr size_t getNumChannels() const { return numChannels_; }
    _INLINE_ constexpr size_t getNumSamples() const { return numSamples_; }

    _INLINE_ SampleIdx getWriteIdx() const { return writeIdx_; }
    _INLINE_ void advanceWriteIdx() { writeIdx_++; }

    void writeBlock(juce::dsp::AudioBlock<FloatType> block)
    {
        jassert(block.getNumChannels() == numChannels_);
        jassert(block.getNumSamples() <= numSamples_);

        const auto numChannelsToCopy = std::min(block.getNumChannels(), numChannels_);
        const auto numSamplesToCopy = block.getNumSamples();
        for (size_t i = 0; i < numSamplesToCopy; i++)
        {
            for (size_t ch = 0; ch < numChannelsToCopy; ch++)
                buffer_[ch][writeIdx_] = block.getSample(ch, i);
            writeIdx_++;
        }
    }

private:
    HeapBlock<char> storage_;
    dsp::AudioBlock<FloatType> buffer_;
    int32_t writeIdx_;
    size_t numChannels_;
    size_t numSamples_;

};
