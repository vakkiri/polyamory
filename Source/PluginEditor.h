/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <vector>
#include "PAGlo.h"

#define NUM_OSC_SLIDERS 13
struct OscSlider {
    Slider levelSlider;
    Slider pitchSlider;
    Slider freqSlider;
    Slider centerSlider;
    Slider lSlopeSlider;
    Slider rSlopeSlider;
    Slider lCurveSlider;
    Slider rCurveSlider;
    Slider noiseSlider;
    Slider aSlider;
    Slider dSlider;
    Slider sSlider;
    Slider rSlider;
};

//==============================================================================
/**
*/
class PolyamoryAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    PolyamoryAudioProcessorEditor (PolyamoryAudioProcessor&);
    ~PolyamoryAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void initSliderPositions();
    void sliderValueChanged (Slider* slider) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolyamoryAudioProcessor& processor;
    
    OscSlider   oscSliders[NUM_OSCS];
    Label       sliderLabels[NUM_OSC_SLIDERS];
    Slider      aSlider;
    Slider      dSlider;
    Slider      sSlider;
    Slider      rSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyamoryAudioProcessorEditor)
};
