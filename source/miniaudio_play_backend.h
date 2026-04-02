#pragma once

#include "buffer.h"
#include <miniaudio.h>

namespace RustyAudio
{

class MiniaudioPlayBackend
{
public:
    MiniaudioPlayBackend(Buffer& soundBuffer);
    ~MiniaudioPlayBackend();

    void play();
    void pause();
    void stop();
    bool isPlaying() const;
    bool isLooping() const;
    void setLooping(bool looping);

private:
    Buffer& mSoundBuffer;
    ma_engine mEngine;
    ma_sound mSound;
    ma_audio_buffer mAudioBuffer;
    bool mLooping;
};

}
