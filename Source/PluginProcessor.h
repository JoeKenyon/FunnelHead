/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Funnel.h"
#include "BandSplitter.h"


//==============================================================================
/**
*/

class FunnelHeadAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FunnelHeadAudioProcessor();
    ~FunnelHeadAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void setVolume(double _volume){ volume.setGainLinear(_volume);}
    void setPreGain(double _pregain){ funnel.setDrive(_pregain);}
    void setSplitFreq(double _splitfreq){ bandSplitter.setSplitFreq(_splitfreq);}
    void setLows(double _lows){ bandSplitter.setLowGain(_lows);}
    void setHighs(double _highs){ bandSplitter.setHighGain(_highs);}
    void setPostGain(double _postgain){ postGain.setGainDecibels(_postgain);}

private: 
    
    Funnel funnel;
    juce::dsp::Gain<float> postGain;
    BandSplitter bandSplitter;
    juce::dsp::Convolution convolution;
    juce::dsp::Gain<float> volume;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnelHeadAudioProcessor)
};


