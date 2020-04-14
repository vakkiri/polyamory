/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>

class PAVoice;
class PAOscillator;

//==============================================================================
/**
*/
class PolyamoryAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PolyamoryAudioProcessor();
    ~PolyamoryAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void setOscCenter(int osc, float val);
    void setOscFreq(int osc, float val);
    void setOscPitch(int osc, float val);
    void setOscLslope(int osc, float val);
    void setOscRslope(int osc, float val);
    void setOscLcurve(int osc, float val);
    void setOscRcurve(int osc, float val);
    void setOscLevel(int osc, float val);
    void setOscNoise(int osc, float val);
    
    void setA(float val);
    void setD(float val);
    void setS(float val);
    void setR(float val);
private:
    //==============================================================================
    Synthesiser                 synth;
    std::vector<PAVoice*>       voices;
    std::vector<PAOscillator*>  oscs;   // TODO: use these instead of having per voice oscs

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyamoryAudioProcessor)
};
