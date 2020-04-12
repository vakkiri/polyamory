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
    private:
        float getSample(unsigned int pos, float center, float lslope, float rslope, float curve, float noise);
};