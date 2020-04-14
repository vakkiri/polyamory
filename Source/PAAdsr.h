/*
  ==============================================================================

    PAAdsr.h
    Created: 12 Apr 2020 5:45:03pm
    Author:  lain

  ==============================================================================
*/

#pragma once

enum PAAdsrState {
    PA_ATTACK,
    PA_SUSTAIN,
    PA_RELEASE,
    PA_VOICEOFF
};

class PAAdsr {
    public:
        PAAdsr();
        void start();
        void stop();
        void update();
        float val();
        bool active();
        
        void setA(float val) {a = val;}
        void setD(float val) {d = val;}
        void setS(float val) {s = val;}
        void setR(float val) {s = val;}
    private:
        float time;
        float a, d, s, r;
        PAAdsrState state;
};
