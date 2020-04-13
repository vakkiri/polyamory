/*
  ==============================================================================

    PANoteMapper.h
    Created: 11 Apr 2020 1:48:51pm
    Author:  lain

  ==============================================================================
*/

#pragma once

#include <string>

class PANoteMapper {
    public:
        PANoteMapper();
        ~PANoteMapper();
        float getFreq(int key);
        void setKeyFreq(int key, float freq);
        void setKeyFreqs(std::string tun_path);
    private:
        float *noteFreqs;
        void initKeyFreqs();
};