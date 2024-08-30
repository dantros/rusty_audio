#pragma once

#include "player.h"
#include "buffer.h"
#include <memory>
#include <miniaudio.h>

namespace RustyAudio
{

class Player::PlayerImpl
{
public:
    PlayerImpl(Buffer& soundBuffer);
    ~PlayerImpl();

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
