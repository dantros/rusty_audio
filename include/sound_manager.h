#pragma once

#include <memory>
#include "note.h"

namespace RustyAudio
{

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