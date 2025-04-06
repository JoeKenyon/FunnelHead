/*
  ==============================================================================

    WaveShapers.h
    Created: 31 Mar 2025 7:28:36pm
    Author:  Joe Kenyon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveShapers
{
public:
    static float Tanh(float x)
    {
        return juce::dsp::FastMathApproximations::tanh(x);
    }
    // use waveshaper found in desmos file
    // uses exponential function
    // modified slightly
    // https://www.desmos.com/calculator/oaybhn0jp5
    static float CustomOne(float x)
    {
        float x17 = x * 1.7f;
        return 1.5 * ((sigmoid(x17) *(1+x17*(1-sigmoid(x17)))) - 0.5);
    }
    // exp based wave shaper
    // modified it slightly
    // https://www.desmos.com/calculator/nhwmmnjdek
    static float Exponetional(float x)
    {
        return (sigmoid(x)-0.5f)*2;
    }
private:
    /*
        1
     ---------
     1 + e^(-x)
     */
    static float sigmoid(float x)
    {
        return 1/(1+juce::dsp::FastMathApproximations::exp(-x));
    }
};
