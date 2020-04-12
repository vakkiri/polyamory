/*
  ==============================================================================

    PAWaveGenerator.cpp
    Created: 11 Apr 2020 5:41:24pm
    Author:  lain

  ==============================================================================
*/

#include <iostream>

#include "PAGlo.h"
#include "PAWaveGenerator.h"

#define HALF        (SAMPLE_RATE * center)
#define LEFT_START  (HALF * lslope)
#define RIGHT_START (SAMPLE_RATE - ((SAMPLE_RATE - HALF) * rslope))

PAWaveGenerator::PAWaveGenerator() {
}

float PAWaveGenerator::getSample(unsigned int pos, float center, float lslope, float rslope, float curve, float noise) {
    float sample = 0.f;
    
    // constraint check
    if (pos >= SAMPLE_RATE) {
        pos = pos % SAMPLE_RATE;
    }
    if (    center < 0.f || center > 1.f ||
            lslope < 0.f || lslope > 1.f ||
            rslope < 0.f || rslope > 1.f ||
            curve < 0.f || curve > 1.f ||
            noise < 0.f || noise > 1.f ) {
                // leave the sample at 0.f
                std::cout << "At least one paramter out of range when retrieving sample from wave generator.\n";
    }
    else {
        if (pos < HALF) {
            if (pos < LEFT_START) {
                // TODO: mix this with a sin based on curve amt - but only for start..left and right..end
                sample =  -1.f + (2.f * ((float)(pos - LEFT_START) / (float)(HALF - LEFT_START)));
            }
            else {
                sample = -1.f;
            }
        }
        else {
            if (pos > RIGHT_START) {
                sample = 1.f - (2.f * ((float)(pos - RIGHT_START) / (double)(SAMPLE_RATE - RIGHT_START)));
            }
            else {
                sample = 1.f;
            }
        }
    }
    
    return sample;
}