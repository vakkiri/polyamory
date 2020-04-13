/*
  ==============================================================================

    PAWaveGenerator.h
    Created: 11 Apr 2020 5:41:24pm
    Author:  lain

  ==============================================================================
*/

#pragma once

class PAWaveGenerator {
    public:
        PAWaveGenerator();
        float getSample(float pos, float center, float lslope, float rslope, float lcurve, float rcurve, float noise);
};