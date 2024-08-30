#pragma once

#include <memory>
#include <buffer.h>

namespace RustyAudio
{

class Player
{
public:
    Player();
    ~Player();

    void init(Buffer& soundBuffer);
    void play();
    void pause();
    void stop();
    bool isPlaying() const;
    bool isLooping() const;
    void setLooping(bool looping);

private:
    class PlayerImpl;
    std::unique_ptr<PlayerImpl> mSoundPlayerImpl;
};

}
