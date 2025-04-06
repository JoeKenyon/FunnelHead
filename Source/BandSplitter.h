/*
  ==============================================================================

    BandSplitter.h
    Created: 29 Mar 2025 1:38:31pm
    Author:  Joe Kenyon

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "Funnel.h"

class BandSplitter : juce::dsp::ProcessorBase
{

public:
    BandSplitter()
    {
        lowGain.setRampDurationSeconds(0.1);
        highGain.setRampDurationSeconds(0.1);
        lowpass .setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
        highpass.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    }
    
    void setLowGain(float newLowGain)
    {
        lowGain.setGainDecibels(newLowGain);
    }
    
    void setHighGain(float newHighGain)
    {
        highGain.setGainDecibels(newHighGain);
    }
    
    void setSplitFreq(float newSplitFreq)
    {
        lowpass.setCutoffFrequency(newSplitFreq);
        highpass.setCutoffFrequency(newSplitFreq);
    }
    
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        lowpass.prepare(spec);
        highpass.prepare(spec);
        lowGain.prepare(spec);
        highGain.prepare(spec);

        // 4 channels 2 for each band
        buffer.setSize (4, int (spec.maximumBlockSize), false, false, true);
    }

    void reset()
    {
        lowpass.reset();
        highpass.reset();
        lowGain.reset();
        highGain.reset();
    }

    void process(const juce::dsp::ProcessContextReplacing<float>& context)
    {
        const auto& inputBlock = context.getInputBlock();

        const size_t numSamples  = inputBlock.getNumSamples();
        const size_t numChannels = inputBlock.getNumChannels();

        auto sepBlock  = juce::dsp::AudioBlock<float>(buffer).getSubBlock(0,numSamples);
        auto lowBlock  = sepBlock.getSubsetChannelBlock(0, numChannels);
        auto highBlock = sepBlock.getSubsetChannelBlock(2, numChannels);

        lowBlock .copyFrom(inputBlock);
        highBlock.copyFrom(inputBlock);

        auto lowContext = juce::dsp::ProcessContextReplacing<float>(lowBlock);
        lowContext.isBypassed = context.isBypassed;

        lowpass.process(lowContext);
        lowGain.process(lowContext);

        auto highContext = juce::dsp::ProcessContextReplacing<float>(highBlock);
        highContext.isBypassed = context.isBypassed;
        
        highpass.process(highContext);
        highGain.process(highContext);
        
        lowBlock.add(highBlock);
        context.getOutputBlock().copyFrom(lowBlock);
    }


    juce::dsp::Gain<float> lowGain;
    juce::dsp::Gain<float> highGain;
    juce::dsp::LinkwitzRileyFilter<float> lowpass;
    juce::dsp::LinkwitzRileyFilter<float> highpass;
    juce::AudioBuffer<float> buffer;
};
