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
        //1378 × 399
    setSize (970, 400);
    
    background = background = juce::ImageCache::getFromMemory(BinaryData::funnelHeadBack_png, BinaryData::funnelHeadBack_pngSize);
    
    addAndMakeVisible(volume);
    volume.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    volume.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    volume.setRange(juce::Range<double>(0, 100), 1);
    volume.setValue(100);
    volume.setTextValueSuffix("%");
    volume.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    volume.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black);
    volume.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    volume.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    volume.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    volume.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    volume.setMouseDragSensitivity(450);
    volume.onValueChange = [this]()
    {
        audioProcessor.setVolume(volume.getValue()*0.01);
    };
    
    addAndMakeVisible(pregain);
    pregain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    pregain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    pregain.setRange(juce::Range<double>(0, 35), 0.1); // db
    pregain.setTextValueSuffix("dB");
    pregain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    pregain.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    pregain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    pregain.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    pregain.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    pregain.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    pregain.setMouseDragSensitivity(450);
    pregain.onValueChange = [this]()
    {
        audioProcessor.setPreGain(pregain.getValue());
    };
    pregain.setValue(0);
    
    addAndMakeVisible(splitfreq);
    splitfreq.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    splitfreq.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    splitfreq.setRange(juce::Range<double>(100, 6000), 1); // db
    splitfreq.setValue(1000);
    splitfreq.setTextValueSuffix("Hz");
    splitfreq.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    splitfreq.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    splitfreq.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    splitfreq.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    splitfreq.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    splitfreq.setColour(juce::Slider::ColourIds::textBoxOutlineColourId,juce::Colours::white.withAlpha(0.6f));
    splitfreq.setMouseDragSensitivity(450);
    splitfreq.onValueChange = [this]()
    {
        audioProcessor.setSplitFreq(splitfreq.getValue());
    };
    
    addAndMakeVisible(lows);
    lows.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    lows.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    lows.setRange(juce::Range<double>(-10, 10), 0.1); // db
    lows.setValue(0);
    lows.setTextValueSuffix("dB");
    lows.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    lows.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    lows.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    lows.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    lows.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    lows.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    lows.setMouseDragSensitivity(450);
    lows.onValueChange = [this]()
    {
        audioProcessor.setLows(lows.getValue());
    };
    
    addAndMakeVisible(highs);
    highs.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    highs.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    highs.setRange(juce::Range<double>(-10, 10), 0.1); // db
    highs.setValue(0);
    highs.setTextValueSuffix("dB");
    highs.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    highs.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    highs.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    highs.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    highs.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    highs.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    highs.setMouseDragSensitivity(450);
    highs.onValueChange = [this]()
    {
        audioProcessor.setHighs(highs.getValue());
    };
    
    addAndMakeVisible(postgain);
    postgain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    postgain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    postgain.setRange(juce::Range<double>(-10, 10), 0.1); // db
    postgain.setValue(0);
    postgain.setTextValueSuffix("dB");
    postgain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    postgain.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    postgain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    postgain.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    postgain.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::white.withAlpha(0.6f));
    postgain.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white.withAlpha(0.6f));
    postgain.setMouseDragSensitivity(450);
    postgain.onValueChange = [this]()
    {
        audioProcessor.setPostGain(postgain.getValue());
    };
    
    setResizable(false, false);
}

FunnelHeadAudioProcessorEditor::~FunnelHeadAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
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
