/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PAGlo.h"

//==============================================================================
PolyamoryAudioProcessorEditor::PolyamoryAudioProcessorEditor (PolyamoryAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1600, 512);
    
    initSliderPositions();
}

PolyamoryAudioProcessorEditor::~PolyamoryAudioProcessorEditor()
{
}

//==============================================================================
void PolyamoryAudioProcessorEditor::initSliderPositions() {
    // Oscillators
    for (int osc = 0; osc < NUM_OSCS; ++osc) {
        Slider* s = (Slider*) &(oscSliders[osc]);
        for (int slider = 0; slider < NUM_OSC_SLIDERS; ++slider, ++s) {
            s->setSliderStyle(Slider::SliderStyle::Rotary);
            s->setTextBoxStyle( Slider::TextEntryBoxPosition::TextBoxBelow, false, 64.f, 16.f );
            addAndMakeVisible (*s);
            s->setRange (0.f, 1.f, 0.01);
            s->addListener (this);
        }
        oscSliders[osc].freqSlider.setRange(-20.f, 20.f, 0.5f);
    }

    for (int i = 0; i < NUM_OSC_SLIDERS; ++i) {
        addAndMakeVisible(sliderLabels[i]);
    }
    
    sliderLabels[0].setText("Level", dontSendNotification);
    sliderLabels[1].setText("Pitch", dontSendNotification);
    sliderLabels[2].setText("Freq", dontSendNotification);
    sliderLabels[3].setText("Center", dontSendNotification);
    sliderLabels[4].setText("L Start", dontSendNotification);
    sliderLabels[5].setText("R Start", dontSendNotification);
    sliderLabels[6].setText("L Curve", dontSendNotification);
    sliderLabels[7].setText("R Curve", dontSendNotification);
    sliderLabels[8].setText("Noise", dontSendNotification);
    sliderLabels[9].setText("A", dontSendNotification);
    sliderLabels[10].setText("D", dontSendNotification);
    sliderLabels[11].setText("S", dontSendNotification);
    sliderLabels[12].setText("R", dontSendNotification);
    
    // Master
    aSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    aSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 64.f, 16.f);
    aSlider.setRange(0.f, 10.f, 0.001f);
    aSlider.addListener(this);
    addAndMakeVisible(aSlider);
    
    dSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    dSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 64.f, 16.f);
    dSlider.setRange(0.f, 10.f, 0.001f);
    dSlider.addListener(this);
    addAndMakeVisible(dSlider);
    
    sSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    sSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 64.f, 16.f);
    sSlider.setRange(0.f, 1.f, 0.001f);
    sSlider.addListener(this);
    addAndMakeVisible(sSlider);
    
    rSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    rSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 64.f, 16.f);
    rSlider.setRange(0.f, 10.f, 0.001f);
    rSlider.addListener(this);
    addAndMakeVisible(rSlider);
}

void PolyamoryAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void PolyamoryAudioProcessorEditor::resized()
{
    // Oscillators
    for (int osc = 0; osc < NUM_OSCS; ++osc) {
        Slider* s = (Slider*) &(oscSliders[osc]);
        for (int slider = 0; slider < NUM_OSC_SLIDERS; ++slider, ++s) {
            s->setBounds(16 + (86 * slider), 32 + (64 * osc), 86, 64);
        }
    }
    for (int label = 0; label < NUM_OSC_SLIDERS; ++label) {
        sliderLabels[label].setBounds(16 + (86 * label), 8, 86, 24);
    }
    
    // Master
    rSlider.setBounds(1600 - 16 - 86,           32, 86, 64);
    sSlider.setBounds(1600 - 16 - (86 * 2),     32, 86, 64);
    dSlider.setBounds(1600 - 16 - (86 * 3),     32, 86, 64);
    aSlider.setBounds(1600 - 16 - (86 * 4),     32, 86, 64);
}

void PolyamoryAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    // Oscillator Frequency offset
    if (slider == (&(oscSliders[0].freqSlider))) {
        processor.setOscFreq(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].freqSlider))) {
        processor.setOscFreq(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].freqSlider))) {
        processor.setOscFreq(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].freqSlider))) {
        processor.setOscFreq(3, slider->getValue());
    }
    // Center offset
    else if (slider == (&(oscSliders[0].centerSlider))) {
        processor.setOscCenter(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].centerSlider))) {
        processor.setOscCenter(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].centerSlider))) {
        processor.setOscCenter(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].centerSlider))) {
        processor.setOscCenter(3, slider->getValue());
    }
    // Oscillator Level
    else if (slider == (&(oscSliders[0].levelSlider))) {
        processor.setOscLevel(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].levelSlider))) {
        processor.setOscLevel(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].levelSlider))) {
        processor.setOscLevel(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].levelSlider))) {
        processor.setOscLevel(3, slider->getValue());
    }
    // Oscillator left slope start
    else if (slider == (&(oscSliders[0].lSlopeSlider))) {
        processor.setOscLslope(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].lSlopeSlider))) {
        processor.setOscLslope(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].lSlopeSlider))) {
        processor.setOscLslope(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].lSlopeSlider))) {
        processor.setOscLslope(3, slider->getValue());
    }
    // Oscillator right slope end
    else if (slider == (&(oscSliders[0].rSlopeSlider))) {
        processor.setOscRslope(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].rSlopeSlider))) {
        processor.setOscRslope(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].rSlopeSlider))) {
        processor.setOscRslope(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].rSlopeSlider))) {
        processor.setOscRslope(3, slider->getValue());
    }
    // Oscillator left curve
    else if (slider == (&(oscSliders[0].lCurveSlider))) {
        processor.setOscLcurve(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].lCurveSlider))) {
        processor.setOscLcurve(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].lCurveSlider))) {
        processor.setOscLcurve(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].lCurveSlider))) {
        processor.setOscLcurve(3, slider->getValue());
    }
    // Oscillator right curve
    else if (slider == (&(oscSliders[0].rCurveSlider))) {
        processor.setOscRcurve(0, slider->getValue());
    }
    else if (slider == (&(oscSliders[1].rCurveSlider))) {
        processor.setOscRcurve(1, slider->getValue());
    }
    else if (slider == (&(oscSliders[2].rCurveSlider))) {
        processor.setOscRcurve(2, slider->getValue());
    }
    else if (slider == (&(oscSliders[3].rCurveSlider))) {
        processor.setOscRcurve(3, slider->getValue());
    }
    
    // Master ADSR
    else if (slider == &aSlider) {
        processor.setA(slider->getValue());
    }
    else if (slider == &dSlider) {
        processor.setD(slider->getValue());
    }
    else if (slider == &sSlider) {
        processor.setS(slider->getValue());
    }
    else if (slider == &rSlider) {
        processor.setR(slider->getValue());
    }
}