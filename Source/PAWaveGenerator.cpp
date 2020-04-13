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
#define RIGHT_END   (HALF + (SAMPLE_RATE - HALF) * rslope)

PAWaveGenerator::PAWaveGenerator() {
}

float PAWaveGenerator::getSample(float pos, float center, float lslope, float rslope, float lcurve, float rcurve, float noise) {
    float sample = 0.f;
    
    // constraint checks
    while (pos >= SAMPLE_RATE) {
        pos -= SAMPLE_RATE;
    }
    if (    center < 0.f || center > 1.f ||
            lslope < 0.f || lslope > 1.f ||
            rslope < 0.f || rslope > 1.f ||
            lcurve < 0.f || lcurve > 1.f ||
            rcurve < 0.f || rcurve > 1.f ||
            noise < 0.f || noise > 1.f ) {
                // leave the sample at 0.f. could instead bound the  faulty paramter, TODO?
                std::cout << "At least one paramter out of range when retrieving sample from wave generator.\n";
    }
    else {
        if (pos < HALF) {
            if (pos < LEFT_START) {
                // TODO: mix this with a sin based on lcurve amt - but only for start..left 
                sample =  -1.f + (2.f * (pos / LEFT_START));
            }
            else {
                sample = 1.f;
            }
        }
        else {
            if (pos < RIGHT_END) {
                sample = 1.f - (2.f * ((pos - HALF) / (RIGHT_END - HALF)));
            }
            else {
                sample = -1.f;
            }
        }
    }
    
    return sample;
}