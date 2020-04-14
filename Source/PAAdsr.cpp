/*
  ==============================================================================

    PAAdsr.cpp
    Created: 12 Apr 2020 5:45:03pm
    Author:  lain

  ==============================================================================
*/

#include<iostream>

#include "PAAdsr.h"
#include "PAGlo.h"

#define A (a * SAMPLE_RATE)
#define D (d * SAMPLE_RATE)
#define R (r * SAMPLE_RATE)

PAAdsr::PAAdsr() {
    time = 0;
    state = PA_VOICEOFF;
    a = 0.1f;
    d = 0.5f;
    s = 1.f;
    r = 4.f;
}

void PAAdsr::start() {
    time = 0;
    state = PA_ATTACK;
}

void PAAdsr::stop() {
    state = PA_RELEASE;
    time = 0;
}

bool PAAdsr::active() {
    return (state != PA_VOICEOFF);
}

void PAAdsr::update() {
    if (state == PA_ATTACK) {
        if (time < A) {
            time += 1;  // TODO: should be relative to sample rate
        }
        else {
            state = PA_SUSTAIN;
            time = 0;
        }
    }
    else if (state == PA_SUSTAIN) {
        if (time < D) {
            time += 1;
        }
        else {
            time = D;
        }
    }
    else if (state == PA_RELEASE) {
        if (time < R) {
            time += 1;
        }
        else {
            state = PA_VOICEOFF;
        }
    }
}

float PAAdsr::val() {
    float out;
    
    switch(state) {
        case PA_ATTACK:
            out = time / A;
            break;
        case PA_SUSTAIN:
            out = 1.f - ((1.f - s) * (time / D));
            break;
        case PA_RELEASE:
            out = s * ((R - time) / R);
            break;
        case PA_VOICEOFF:
        default:
            out = 0.f;
    }
    
    return out;
}

