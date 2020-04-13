/*
  ==============================================================================

    PAGlo.cpp
    Created: 12 Apr 2020 5:22:15pm
    Author:  lain

  ==============================================================================
*/

#include "PAGlo.h"
#include "PANoteMapper.h"
#include "PAWaveGenerator.h"

float               gloSampleRate;
unsigned int        numVoices;
unsigned int        numOscs;
PANoteMapper*       noteMapper;
PAWaveGenerator*    waveGen;

void gloInit() {
    noteMapper  = new PANoteMapper;
    waveGen     = new PAWaveGenerator;
}

void gloFinish() {
    if (noteMapper != nullptr)
        delete noteMapper;
    if (waveGen != nullptr)
        delete waveGen;
}