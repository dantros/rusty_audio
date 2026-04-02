
#include "player.h"
#include "play_backend.h"
#include <memory>

namespace RustyAudio
{

// PlayerImpl inherits from the selected play backend.
// Defined here so backend headers stay out of the public API.
class Player::PlayerImpl : public SelectedPlayBackend
{
public:
    using SelectedPlayBackend::SelectedPlayBackend;
};

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(Buffer& soundBuffer)
{
    mSoundPlayerImpl = std::make_unique<PlayerImpl>(soundBuffer);
}

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
