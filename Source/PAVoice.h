/*
  ==============================================================================

    PAVoice.h
    Created: 12 Apr 2020 5:15:25pm
    Author:  lain

  ==============================================================================
*/

#pragma once
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"

class PAAdsr;
class PAOscillator;

class PAVoice : public SynthesiserVoice {
    public:
        PAVoice();
        ~PAVoice();
        
        virtual bool canPlaySound(SynthesiserSound *sound);
        virtual bool isVoiceActive();
        virtual void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition);
        virtual void stopNote(float velocity, bool allowTailOff);
        virtual void pitchWheelMoved(int newPitchWheelValue);
        virtual void controllerMoved(int controllerNumber, int newControllerValue);
        virtual void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    protected: 
        virtual void perSampleUpdate();
        
        std::vector<PAOscillator*> oscs;
        PAAdsr *adsr;
        float voiceFreq;
        bool wasActive;
};