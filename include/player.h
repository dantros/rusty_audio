#pragma once

#include <memory>
#include <buffer.h>

namespace RustyAudio
{

class Player
{
public:
    Player(Buffer& soundBuffer);
    ~Player();

    void play();
    void pause();
    void stop();
    bool isPlaying() const;

private:
    class SoundPlayerImpl;
    std::unique_ptr<SoundPlayerImpl> mSoundPlayerImpl;
};

}
