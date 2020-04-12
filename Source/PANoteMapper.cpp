/*
  ==============================================================================

    PANoteMapper.cpp
    Created: 11 Apr 2020 1:48:51pm
    Author:  lain

  ==============================================================================
*/

#include <cmath>
#include <iostream>
#include "PANoteMapper.h"

PANoteMapper::PANoteMapper() {
    initKeyFreqs();
}

void PANoteMapper::initKeyFreqs() {
    for (int i = 0; i < NUM_MIDI_KEYS; ++i)
        noteFreqs[i] = 440 * (pow(2, (i - 69) / 12));
}

void PANoteMapper::setKeyFreq(unsigned int key, float freq) {
    if (key >= NUM_MIDI_KEYS)
        std::cout << "Cannot set frequency for key " << key << std::endl;
    else if (freq <= 0.f)
        std::cout << "Cannot use frequency " << freq << std::endl;
    else
        noteFreqs[key] = freq;
}

void PANoteMapper::setKeyFreqs(std::string tun_path) {
    std::cout << "Loading tun file not implemented yet.\n";
}

float PANoteMapper::getFreq(unsigned int key) {
    return noteFreqs[key];
}
