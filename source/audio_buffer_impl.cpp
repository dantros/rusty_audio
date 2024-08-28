#include "audio_buffer_impl.h"

#include <miniaudio.h>
#include <thread>
#include <chrono>
#include <cassert>

#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  48000

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_waveform* pSineWave;

    assert(pDevice->playback.channels == DEVICE_CHANNELS);

    pSineWave = (ma_waveform*)pDevice->pUserData;
    assert(pSineWave != NULL);

    ma_waveform_read_pcm_frames(pSineWave, pOutput, frameCount, NULL);
}

namespace RustyAudio
{

AudioBuffer::AudioBufferImpl::AudioBufferImpl()
{
    ma_device device;
    std::chrono::milliseconds duration{ 5000 };
    double amplitude = 1.0;
    double frecuency = 493.883;
    //---

    ma_waveform sineWave;
    ma_device_config deviceConfig;
    
    ma_waveform_config sineWaveConfig;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = DEVICE_FORMAT;
    deviceConfig.playback.channels = DEVICE_CHANNELS;
    deviceConfig.sampleRate = DEVICE_SAMPLE_RATE;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &sineWave;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        throw;
    }

    //printf("Device Name: %s\n", device.playback.name);

    sineWaveConfig = ma_waveform_config_init(
        device.playback.format,
        device.playback.channels,
        device.sampleRate,
        ma_waveform_type_sine,
        amplitude,
        frecuency);
    ma_waveform_init(&sineWaveConfig, &sineWave);

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        throw;
    }
    
    std::this_thread::sleep_for(duration);

    ma_device_uninit(&device);
}

AudioBuffer::AudioBufferImpl::~AudioBufferImpl()
{
    
}

}