#pragma once

#include "player.h"
#include "buffer.h"
#include <memory>
#include <miniaudio.h>

namespace RustyAudio
{

class SoundPlayer::SoundPlayerImpl
{
public:
    SoundPlayerImpl(SoundBuffer& soundBuffer);
    ~SoundPlayerImpl();

    void play();
    void pause();
    void stop();
    bool isPlaying() const;

private:
    SoundBuffer& mSoundBuffer;
    ma_engine g_engine;
    ma_sound g_sound;
    ma_audio_buffer audioBuffer;
};

}
