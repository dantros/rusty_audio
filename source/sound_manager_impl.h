#pragma once

#include <rusty_audio.h>
#include <miniaudio.h>
#include <deque>

namespace RustyAudio
{

class SoundManager::SoundManagerImpl
{
public:    
    SoundManagerImpl();

    void scheduleNote(const Note& note);

    void playNext();

    void tick(float milliseconds);

    ~SoundManagerImpl();
    
private:
    ma_device device;
    ma_waveform sineWave;
    float timer;
    
    std::deque<Note> schedule;
};

}