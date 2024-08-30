
#include "player.h"
#include "player_impl.h"

namespace RustyAudio
{

Player::Player(Buffer& soundBuffer)
{
    mSoundPlayerImpl = std::make_unique<PlayerImpl>(soundBuffer);
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

bool Player::isLooping() const
{
    return mSoundPlayerImpl->isLooping();
}

void Player::setLooping(bool looping)
{
    mSoundPlayerImpl->setLooping(looping);
}

}
