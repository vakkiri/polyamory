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
#include "PAGlo.h"

PANoteMapper::PANoteMapper() {
    noteFreqs = new float[NUM_MIDI_KEYS];
    initKeyFreqs();
}

PANoteMapper::~PANoteMapper() {
    delete [] noteFreqs;
}

void PANoteMapper::initKeyFreqs() {
    for (int i = 0; i < NUM_MIDI_KEYS; ++i)
        noteFreqs[i] = 440.f * ((float)pow(2.f, ((float)i - 69.f) / 12.f));
}

void PANoteMapper::setKeyFreq(int key, float freq) {
    if (key < 0 || key >= NUM_MIDI_KEYS)
        std::cout << "Cannot set frequency for key " << key << std::endl;
    else if (freq <= 0.f)
        std::cout << "Cannot use frequency " << freq << std::endl;
    else
        noteFreqs[key] = freq;
}

void PANoteMapper::setKeyFreqs(std::string tun_path) {
    std::cout << "Loading tun file not implemented yet.\n";
}

float PANoteMapper::getFreq(int key) {
    if (key < 0 || key >= NUM_MIDI_KEYS) {
        std::cout << "Cannot get frequency for key " << key << std::endl;
        return 0.f;
    }
    
    return noteFreqs[key];
}
