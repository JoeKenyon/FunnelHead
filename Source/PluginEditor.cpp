/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FunnelHeadAudioProcessorEditor::FunnelHeadAudioProcessorEditor (FunnelHeadAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    background = background = juce::ImageCache::getFromMemory(BinaryData::funnelHeadBack_png, BinaryData::funnelHeadBack_pngSize);
    
    addAndMakeVisible(volume);
    volumeAt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.pvms, "volume", volume);
    volume.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    volume.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    volume.setTextValueSuffix("%");
    volume.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    volume.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black);
    volume.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    volume.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    volume.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    volume.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    volume.setMouseDragSensitivity(650);
    
    addAndMakeVisible(pregain);
    pregainAt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.pvms,"pregain",pregain);
    pregain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    pregain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    pregain.setTextValueSuffix("dB");
    pregain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    pregain.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    pregain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    pregain.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    pregain.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    pregain.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    pregain.setMouseDragSensitivity(650);
    
    addAndMakeVisible(postgain);
    postgainAt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.pvms,"postgain",postgain);
    postgain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    postgain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    postgain.setTextValueSuffix("dB");
    postgain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    postgain.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    postgain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    postgain.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    postgain.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    postgain.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    postgain.setMouseDragSensitivity(650);
    
    addAndMakeVisible(splitfreq);
    splitfreqAt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.pvms,"splitfreq",splitfreq);
    splitfreq.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    splitfreq.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    splitfreq.setTextValueSuffix("Hz");
    splitfreq.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    splitfreq.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    splitfreq.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    splitfreq.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    splitfreq.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    splitfreq.setColour(juce::Slider::ColourIds::textBoxOutlineColourId,juce::Colours::white.withAlpha(0.6f));
    splitfreq.setMouseDragSensitivity(650);
    
    addAndMakeVisible(lows);
    lowsAt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.pvms,"lows",lows);
    lows.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    lows.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    lows.setTextValueSuffix("dB");
    lows.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    lows.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    lows.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    lows.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    lows.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    lows.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    lows.setMouseDragSensitivity(650);
    
    addAndMakeVisible(highs);
    highsAt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.pvms,"highs",highs);
    highs.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    highs.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    highs.setTextValueSuffix("dB");
    highs.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    highs.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    highs.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    highs.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    highs.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    highs.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    highs.setMouseDragSensitivity(650);
    
    setSize (970, 400);
    setResizable(false, false);
}

FunnelHeadAudioProcessorEditor::~FunnelHeadAudioProcessorEditor()
{
}

//==============================================================================
void FunnelHeadAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds    = getBounds();
    g.drawImageAt(background, -100,0);
    auto height    = getBounds().getHeight();
    auto width     = getBounds().getWidth();
    auto knobWidth = width/6;
    auto bounds_logo      = bounds.removeFromTop(height*0.6);
    auto bounds_labels    = bounds.removeFromTop(18); // labels
    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(24, juce::Font::bold));
    g.drawText("VOLUME", bounds_labels.removeFromLeft(knobWidth), juce::Justification::centred);
    g.drawText("PREGAIN", bounds_labels.removeFromLeft(knobWidth), juce::Justification::centred);
    g.drawText("POSTGAIN", bounds_labels.removeFromLeft(knobWidth), juce::Justification::centred);
    g.drawText("SPLITFREQ", bounds_labels.removeFromLeft(knobWidth), juce::Justification::centred);
    g.drawText("LOWS", bounds_labels.removeFromLeft(knobWidth), juce::Justification::centred);
    g.drawText("HIGHS", bounds_labels.removeFromLeft(knobWidth), juce::Justification::centred);
}

void FunnelHeadAudioProcessorEditor::resized()
{
    auto bounds    = getBounds();
    auto height    = getBounds().getHeight();
    auto width     = getBounds().getWidth();
    auto knobWidth = width/6;
    auto bounds_logo      = bounds.removeFromTop(height*0.6);
    auto bounds_labels    = bounds.removeFromTop(15); // labels
    auto bounds_volume    = bounds.removeFromLeft(knobWidth);
    auto bounds_pregain   = bounds.removeFromLeft(knobWidth);
    auto bounds_postgain  = bounds.removeFromLeft(knobWidth);
    auto bounds_splitfreq = bounds.removeFromLeft(knobWidth);
    auto bounds_lows      = bounds.removeFromLeft(knobWidth);
    auto bounds_highs     = bounds.removeFromLeft(knobWidth);
    
    volume.setBounds(bounds_volume);
    pregain.setBounds(bounds_pregain);
    postgain.setBounds(bounds_postgain);
    splitfreq.setBounds(bounds_splitfreq);
    lows.setBounds(bounds_lows);
    highs.setBounds(bounds_highs);
}
