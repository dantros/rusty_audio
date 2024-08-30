
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
    result = ma_engine_init(NULL, &g_engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        throw;
    }

    std::int32_t* pExistingData = mSoundBuffer.data();
    
    ma_audio_buffer_config config = ma_audio_buffer_config_init(ma_format_s32, mSoundBuffer.channels(), mSoundBuffer.frames(), pExistingData, NULL);

    if (ma_audio_buffer_init(&config, &audioBuffer) != MA_SUCCESS) {
        printf("Failed to initialize audio buffer.\n");
        ma_audio_buffer_uninit(&audioBuffer);
        throw;
    }

    if (ma_sound_init_from_data_source(&g_engine, &audioBuffer, 0, NULL, &g_sound) != MA_SUCCESS)
    {
        printf("Failed to initialize sound from data source.\n");
        ma_sound_uninit(&g_sound);
        throw;
    }

    /* Connect the output of the sound to the input of the effect. */
    ma_node_attach_output_bus(&g_sound, 0, ma_engine_get_endpoint(&g_engine), 0);
}

Player::SoundPlayerImpl::~SoundPlayerImpl()
{
    ma_sound_uninit(&g_sound);
    ma_audio_buffer_uninit(&audioBuffer);
    ma_engine_uninit(&g_engine);
}

void Player::SoundPlayerImpl::play()
{
    ma_sound_start(&g_sound);
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
