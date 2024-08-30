
#include "player.h"
#include "player_impl.h"

namespace RustyAudio
{

SoundPlayer::SoundPlayer(SoundBuffer& soundBuffer)
{
    mSoundPlayerImpl = std::make_unique<SoundPlayerImpl>(soundBuffer);
}

SoundPlayer::~SoundPlayer()
{}

void SoundPlayer::play()
{
    mSoundPlayerImpl->play();
}

void SoundPlayer::pause()
{
    mSoundPlayerImpl->pause();
}

void SoundPlayer::stop()
{
    mSoundPlayerImpl->stop();
}

bool SoundPlayer::isPlaying() const
{
    return mSoundPlayerImpl->isPlaying();
}

}
