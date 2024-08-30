#pragma once

#include "player.h"
#include "buffer.h"
#include <memory>
#include <miniaudio.h>

namespace RustyAudio
{

class Player::SoundPlayerImpl
{
public:
    SoundPlayerImpl(Buffer& soundBuffer);
    ~SoundPlayerImpl();

    void play();
    void pause();
    void stop();
    bool isPlaying() const;

private:
    Buffer& mSoundBuffer;
    ma_engine mEngine;
    ma_sound mSound;
    ma_audio_buffer mAudioBuffer;
};

}
