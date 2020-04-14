/*
  ==============================================================================

    PAGlo.h
    Created: 12 Apr 2020 5:22:15pm
    Author:  lain

  ==============================================================================
*/

#pragma once

#define NUM_MIDI_KEYS   128
#define SAMPLE_RATE     gloSampleRate

#define NUM_OSCS        4
#define NUM_VOICES      8

#define VOICE_GAIN      0.3

class PANoteMapper;
class PAWaveGenerator;

extern float            gloSampleRate;
extern unsigned int     numVoices;
extern unsigned int     numOscs;
extern PANoteMapper*    noteMapper;
extern PAWaveGenerator* waveGen;

void gloInit();
void gloFinish();