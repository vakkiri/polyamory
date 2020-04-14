/*
  ==============================================================================

    PAOscillator.cpp
    Created: 13 Apr 2020 8:20:38am
    Author:  lain

  ==============================================================================
*/

#include "PAOscillator.h"
#include "PAGlo.h"

PAOscillator::PAOscillator() {
    level   = 1.0f;
    pitch   = 0.f;
    freq    = 0.f;
    lslope  = 1.f;
    rslope  = 1.f;
    lcurve  = 0.f;
    rcurve  = 0.f;
    center  = 0.5f;
    noise   = 0.f;
    wavePos = 0.f;
}

void PAOscillator::update(float basefreq) {
    wavePos += basefreq + freq; // Todo: also add pitch relative to basefreq
    if (wavePos >= SAMPLE_RATE)
        wavePos -= SAMPLE_RATE;
    if (wavePos < 0)
        wavePos = 0;
}