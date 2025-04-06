/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FunnelHeadAudioProcessor::FunnelHeadAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    const char* ampConvolutionData = BinaryData::American_Twin_2x12_Dark_Mix_wav;
    const int ampConvolutionDataSize = BinaryData::American_Twin_2x12_Dark_Mix_wavSize;
    
    convolution.loadImpulseResponse(ampConvolutionData,
                                   ampConvolutionDataSize,
                                   juce::dsp::Convolution::Stereo::no,
                                 juce::dsp::Convolution::Trim::no,
                                   1024,
                                   juce::dsp::Convolution::Normalise::yes);
}

FunnelHeadAudioProcessor::~FunnelHeadAudioProcessor()
{

}

//==============================================================================
const juce::String FunnelHeadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FunnelHeadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FunnelHeadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FunnelHeadAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FunnelHeadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FunnelHeadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FunnelHeadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FunnelHeadAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FunnelHeadAudioProcessor::getProgramName (int index)
{
    return {};
}

void FunnelHeadAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FunnelHeadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    spec.sampleRate = sampleRate;
    
    funnel.prepare(spec);
    postGain.prepare(spec);
    postGain.setRampDurationSeconds(0.1);
    bandSplitter.prepare(spec);
    volume.prepare(spec);
    volume.setRampDurationSeconds(0.1);
    convolution.prepare(spec);
    
    setVolume(1.0f);
    setPreGain(1.0f);
    setSplitFreq(1000.0f);
    setLows(1.0f);
    setHighs(1.0f);
    setPostGain(1.0f);
}

void FunnelHeadAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FunnelHeadAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FunnelHeadAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    
    funnel.process(context);
    postGain.process(context);
    bandSplitter.process(context);
    volume.process(context);
    convolution.process(context);
}

//==============================================================================
bool FunnelHeadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FunnelHeadAudioProcessor::createEditor()
{
    return new FunnelHeadAudioProcessorEditor(*this);
}

//==============================================================================
void FunnelHeadAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FunnelHeadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FunnelHeadAudioProcessor();
}
