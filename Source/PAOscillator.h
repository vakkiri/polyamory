/*
  ==============================================================================

    PAOscillator.h
    Created: 13 Apr 2020 8:20:38am
    Author:  lain

  ==============================================================================
*/

#pragma once

class PAOscillator {
    public:
        PAOscillator();
        void setCenter(float c) {center = c;}
        void setLslope(float s) {lslope = s;}
        void setRslope(float s) {rslope = s;}
        void setLcurve(float c) {lcurve = c;}
        void setRcurve(float c) {rcurve = c;}
        void setNoise(float n)  {noise = n;}
        void setLevel(float l)  {level = l;}
        void setPitch(float p)  {pitch = p;}
        void setFreq(float f)   {freq = f;}
        float getCenter()       {return center;}
        float getLslope()       {return lslope;}
        float getRslope()       {return rslope;}
        float getLcurve()       {return lcurve;}
        float getRcurve()       {return rcurve;}
        float getNoise()        {return noise;}
        float getLevel()        {return level;}
        float getPitch()        {return pitch;}
        float getFreq()         {return freq;}
        
        float getUpdate(float basefreq, float wavePos);
    private:
        float center;
        float lslope;
        float rslope;
        float lcurve;
        float rcurve;
        float noise;
        float level;
        float pitch;
        float freq;
};