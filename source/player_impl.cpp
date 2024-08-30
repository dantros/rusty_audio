
#include "player_impl.h"

namespace RustyAudio
{

Player::SoundPlayerImpl::SoundPlayerImpl(Buffer& soundBuffer):
    mSoundBuffer(soundBuffer)
{
    ma_result result;

    ma_engine_config engineConfig;
    engineConfig.noDevice = MA_TRUE;
    engineConfig.channels = mSoundBuffer.channels();        // Must be set when not using a device.
    engineConfig.sampleRate = mSoundBuffer.sampleRate();    // Must be set when not using a device.
    result = ma_engine_init(NULL, &mEngine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        throw;
    }

    std::int32_t* pExistingData = mSoundBuffer.data();
    
    ma_audio_buffer_config config = ma_audio_buffer_config_init(ma_format_s32, mSoundBuffer.channels(), mSoundBuffer.frames(), pExistingData, NULL);

    if (ma_audio_buffer_init(&config, &mAudioBuffer) != MA_SUCCESS) {
        printf("Failed to initialize audio buffer.\n");
        ma_audio_buffer_uninit(&mAudioBuffer);
        throw;
    }

    if (ma_sound_init_from_data_source(&mEngine, &mAudioBuffer, 0, NULL, &mSound) != MA_SUCCESS)
    {
        printf("Failed to initialize sound from data source.\n");
        ma_sound_uninit(&mSound);
        throw;
    }

    /* Connect the output of the sound to the input of the effect. */
    ma_node_attach_output_bus(&mSound, 0, ma_engine_get_endpoint(&mEngine), 0);
}

Player::SoundPlayerImpl::~SoundPlayerImpl()
{
    ma_sound_uninit(&mSound);
    ma_audio_buffer_uninit(&mAudioBuffer);
    ma_engine_uninit(&mEngine);
}

void Player::SoundPlayerImpl::play()
{
    ma_sound_start(&mSound);
}

void Player::SoundPlayerImpl::pause()
{

}

void Player::SoundPlayerImpl::stop()
{

}

bool Player::SoundPlayerImpl::isPlaying() const
{
    return false;
}

}
