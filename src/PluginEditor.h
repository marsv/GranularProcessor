#pragma once

#include "PluginProcessor.h"

//==============================================================================
class GranularProcessorPluginEditor  : public juce::AudioProcessorEditor
{
public:
    explicit GranularProcessorPluginEditor (GranularProcessorPlugin&);
    ~GranularProcessorPluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularProcessorPlugin& processor_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularProcessorPluginEditor)
};
