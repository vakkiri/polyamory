/*
  ==============================================================================

    PANoteMapper.h
    Created: 11 Apr 2020 1:48:51pm
    Author:  lain

  ==============================================================================
*/

#pragma once

#include "PAGlo.h"
#include <string>

class PANoteMapper {
    public:
        PANoteMapper();
        float getFreq(unsigned int key);
        void setKeyFreq(unsigned int key, float freq);
        void setKeyFreqs(std::string tun_path);
    private:
        float noteFreqs[NUM_MIDI_KEYS];
        void initKeyFreqs();
};