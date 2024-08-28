
#include <rusty_audio.h>
#include "sound_manager_impl.h"

namespace RustyAudio
{

SoundManager::SoundManager()
{
    mSoundManagerImpl = std::make_unique<SoundManagerImpl>();
}

void SoundManager::scheduleNote(const Note& note)
{
    mSoundManagerImpl->scheduleNote(note);
}

void SoundManager::playNext()
{
    mSoundManagerImpl->playNext();
}

void SoundManager::tick(float milliseconds)
{
    mSoundManagerImpl->tick(milliseconds);
}

SoundManager::~SoundManager()
{

}

}