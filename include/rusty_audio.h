#pragma once

#include <memory>

namespace RustyAudio
{

struct Note
{
    int milliseconds;
    double amplitude, frecuency;
};

class SoundManager
{
public:
    SoundManager();

    void scheduleNote(const Note& note);

    void playNext();

    void tick(float milliseconds);

    ~SoundManager();
private:
    class SoundManagerImpl;
    std::unique_ptr<SoundManagerImpl> mSoundManagerImpl;
};

}