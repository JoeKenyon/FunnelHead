/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FunnelHeadAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FunnelHeadAudioProcessorEditor (FunnelHeadAudioProcessor&);
    ~FunnelHeadAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:   
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FunnelHeadAudioProcessor& audioProcessor;
    juce::Slider volume;
    juce::Slider pregain;
    juce::Slider splitfreq;
    juce::Slider lows;
    juce::Slider highs;
    juce::Slider postgain;
    juce::Image background;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pregainAt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> splitfreqAt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowsAt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highsAt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> postgainAt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnelHeadAudioProcessorEditor)
};
