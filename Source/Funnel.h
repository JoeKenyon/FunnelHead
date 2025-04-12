/*
  ==============================================================================

    Funnel.h
    Created: 29 Mar 2025 1:37:47pm
    Author:  Joe Kenyon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveShapers.h"


class Funnel : juce::dsp::ProcessorBase
{
public:
    Funnel():
        oversampler(2, 4, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR)
    {}
    
    ~Funnel(){}
    
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        oversampler.initProcessing(spec.maximumBlockSize);
        drive.setRampDurationSeconds(0.05);
        drive.prepare(spec);
    }
    
    void reset()
    {
        
    }
    
    void process(const juce::dsp::ProcessContextReplacing<float>& context)
    {
        const auto& inputBlock = context.getInputBlock();
        
        drive.process (context);
        
        auto OSBlock = oversampler.processSamplesUp(inputBlock);
        juce::dsp::ProcessContextReplacing<float> OSContext(OSBlock);
        
        waveShaper.process(OSContext);
        
        auto& outputBlock = context.getOutputBlock();
        oversampler.processSamplesDown(outputBlock);
    }
    
    void setDrive(float newDrive)
    {
        drive.setGainDecibels(newDrive);
    }
        
    juce::dsp::Oversampling<float> oversampler;
    juce::dsp::Gain<float> drive;
    juce::dsp::WaveShaper<float> waveShaper { WaveShapers::Tanh };
};
