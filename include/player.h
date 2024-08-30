#pragma once

#include <memory>
#include <buffer.h>

namespace RustyAudio
{

class SoundPlayer
{
public:
    SoundPlayer(SoundBuffer& soundBuffer);
    ~SoundPlayer();

    void play();
    void pause();
    void stop();
    bool isPlaying() const;

private:
    class SoundPlayerImpl;
    std::unique_ptr<SoundPlayerImpl> mSoundPlayerImpl;
};

}
