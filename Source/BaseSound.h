/*
  ==============================================================================

    BaseSound.h
    Created: 12 Apr 2020 5:04:00pm
    Author:  lain

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class BaseSound : public SynthesiserSound
{
    public:
        //does the sound play when this midi note is pressed?
        virtual bool appliesToNote( int note ) { return true; };
        //or on this channel?
        virtual bool appliesToChannel( int channel ) { return true; };
};