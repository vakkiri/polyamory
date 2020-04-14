/*
  ==============================================================================

    PAVoice.cpp
    Created: 12 Apr 2020 5:15:25pm
    Author:  lain

  ==============================================================================
*/

#include "PAVoice.h"
#include "PAAdsr.h"
#include "PAGlo.h"
#include "PANoteMapper.h"
#include "PAOscillator.h"
#include "PAWaveGenerator.h"

PAVoice::PAVoice() : SynthesiserVoice() {
    voiceFreq = 0;
    adsr = new PAAdsr();
    wasActive = false;

}

PAVoice::~PAVoice() {
    if (adsr != nullptr)
        delete adsr;
    while (!oscs.empty()) {
        delete oscs.back();
        oscs.pop_back();
    }
}

bool PAVoice::canPlaySound(SynthesiserSound *sound) {
    //We will attempt to play any non null sound
    return (sound != nullptr);
}

bool PAVoice::isVoiceActive() {
    return(adsr->active());
}

void PAVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
    voiceFreq = noteMapper->getFreq(midiNoteNumber);
    adsr->start();
}

void PAVoice::stopNote(float velocity, bool allowTailOff) {
    adsr->stop();
}

void PAVoice::pitchWheelMoved(int newPitchWheelValue) {
}

void PAVoice::controllerMoved(int controllerNumber, int newControllerValue) {
}

void PAVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    float val;
    float oscval;
    
    for (int sample = 0; sample < numSamples; ++sample) {
        val = 0;
        
        //sum samples from each oscillator
        for (int i = 0; i < NUM_OSCS; ++i) {
            oscval = waveGen->getSample(    oscPositions[i], 
                                            oscs[i]->getCenter(), 
                                            oscs[i]->getLslope(), 
                                            oscs[i]->getRslope(), 
                                            oscs[i]->getLcurve(), 
                                            oscs[i]->getRcurve(), 
                                            oscs[i]->getNoise()
                                       );
                                            
            oscval *= oscs[i]->getLevel();
            val += oscval;
        }                           
                                        
        //divide by the number of oscs so no values exceed the min or max (-1, 1)
        //TODO: could optionally provide saturation for high values instead
        if (oscs.size() > 0)
            val /= (float) oscs.size();
            
        val *= VOICE_GAIN;
        
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
            outputBuffer.addSample(channel, startSample, val * adsr->val());
        }
        
        perSampleUpdate();
        
        ++startSample;
    }
}

/* perSampleUpdate

    Perform any operations that much be done after calculating every sample,
    such as updating the table position.
*/

void PAVoice::perSampleUpdate() {
    if (adsr->active()) {
        adsr->update();
    
        for (int i = 0; i < oscs.size(); ++i) {
            oscPositions[i] = oscs[i]->getUpdate(voiceFreq, oscPositions[i]);
        }
        
        wasActive = true;
    }
    else if (wasActive) {
           clearCurrentNote();
    }
}

void PAVoice::addOsc(PAOscillator* osc) {
    oscs.push_back(osc);
    oscPositions.push_back(0.f);
}

void PAVoice::setADSRA(float val) {
    adsr->setA(val);
}

void PAVoice::setADSRD(float val) {
    adsr->setD(val);
}


void PAVoice::setADSRS(float val) {
    adsr->setS(val);
}


void PAVoice::setADSRR(float val) {
    adsr->setR(val);
}

