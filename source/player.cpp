
#include "player.h"
#include "player_impl.h"

namespace RustyAudio
{

Player::Player(Buffer& soundBuffer)
{
    mSoundPlayerImpl = std::make_unique<SoundPlayerImpl>(soundBuffer);
}

Player::~Player()
{}

void Player::play()
{
    mSoundPlayerImpl->play();
}

void Player::pause()
{
    mSoundPlayerImpl->pause();
}

void Player::stop()
{
    mSoundPlayerImpl->stop();
}

bool Player::isPlaying() const
{
    return mSoundPlayerImpl->isPlaying();
}

}
