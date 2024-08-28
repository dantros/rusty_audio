
#include "sound_manager_impl.h"
#include <miniaudio.h>
#include <cassert>

#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  48000

namespace RustyAudio
{

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_waveform* pSineWave;

    assert(pDevice->playback.channels == DEVICE_CHANNELS);

    pSineWave = (ma_waveform*)pDevice->pUserData;
    assert(pSineWave != NULL);

    ma_waveform_read_pcm_frames(pSineWave, pOutput, frameCount, NULL);
}

SoundManager::SoundManagerImpl::SoundManagerImpl()
{
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = DEVICE_FORMAT;
    deviceConfig.playback.channels = DEVICE_CHANNELS;
    deviceConfig.sampleRate = DEVICE_SAMPLE_RATE;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &sineWave;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        throw;
    }

    timer = 0.0f;
}

void SoundManager::SoundManagerImpl::scheduleNote(const Note& note)
{
    schedule.push_back(note);
}

void SoundManager::SoundManagerImpl::playNext()
{
    // do we have something on schedule?, if we dont, then just stop the current sound.
    if (schedule.empty())
    {
        ma_device_stop(&device);
        timer = 0.0f;
        return;
    }

    // Getting a copy of the first element
    Note note = schedule.front();

    // Removing the first element from the schedule as we will play it now.
    schedule.pop_front();

    /* Other wave types:
        ma_waveform_type_sine,
        ma_waveform_type_square,
        ma_waveform_type_triangle,
        ma_waveform_type_sawtooth
    */

    ma_waveform_config sineWaveConfig = ma_waveform_config_init(
        device.playback.format,
        device.playback.channels,
        device.sampleRate,
        ma_waveform_type_square, // You can change the wave type!.
        note.amplitude,
        note.frecuency);
    ma_waveform_init(&sineWaveConfig, &sineWave);

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        throw;
    }

    timer = note.milliseconds;
}

void SoundManager::SoundManagerImpl::tick(float milliseconds)
{
    timer -= milliseconds;

    if (timer < 0.0)
    {
        playNext();
    }
}

SoundManager::SoundManagerImpl::~SoundManagerImpl()
{
    ma_device_uninit(&device);
}

}