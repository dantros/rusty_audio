/*
Demonstrates how to apply an effect to sounds using the high level engine API.

This example will load a file from the command line and apply an echo/delay effect to it. It will
show you how to manage `ma_sound` objects and how to insert an effect into the graph.

The `ma_engine` object is a node graph and is compatible with the `ma_node_graph` API. The
`ma_sound` object is a node within the node and is compatible with the `ma_node` API. This means
that applying an effect is as simple as inserting an effect node into the graph and plugging in the
sound's output into the effect's input. See the Node Graph example for how to use the node graph.

This example is playing only a single sound at a time which means only a single `ma_sound` object
it being used. If you want to play multiple sounds at the same time, even if they're for the same
sound file, you need multiple `ma_sound` objects.
*/

#include <cstdint>
#include <vector>
#include <cmath>
#include <limits>
#include <numbers>
#include <cstdio>
#include <miniaudio.h>
#include <buffer.h>

#define DELAY_IN_SECONDS    0.2f
#define DECAY               0.25f   /* Volume falloff for each echo. */

int main(int argc, char** argv)
{
    ma_engine g_engine;
    ma_sound g_sound;            /* This example will play only a single sound at once, so we only need one `ma_sound` object. */
    ma_delay_node g_delayNode;   /* The echo effect is achieved using a delay node. */
    ma_audio_buffer audioBuffer;

    /* The engine needs to be initialized first. */
    ma_engine_config engineConfig;
    /*/#
    engineConfig.noDevice = MA_TRUE;
    engineConfig.channels = 2;        // Must be set when not using a device.
    engineConfig.sampleRate = 1000;    // Must be set when not using a device.
    *///#
    if (ma_engine_init(NULL, &g_engine) != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        return -1;
    }

    /* Audio Buffer */
    const unsigned int durationMs = 5000;
    constexpr float amplitude = 0.5;
    constexpr float frequency_hz = 500.0f;

    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;

    RustyAudio::Buffer soundBuffer;
    soundBuffer.init(sampleRate, channels, durationMs);

    const float frequency_rad = 2 * std::numbers::pi * frequency_hz / 1000;    

    for (size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        /* a representation of time */
        const float timeMs = static_cast<float>(frame * durationMs) / soundBuffer.frames();

        /* sampling a sinusoid */
        const float sample = amplitude * std::sin(frequency_rad * timeMs);

        /* casting it to int32 */
        constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9; // artifacts if we reach the maximum value
        const float scaledSample = MAX_INT32 * sample;
        std::int32_t integerSample = static_cast<std::int32_t>(scaledSample);

        /* A Frame is a convenient facade of the sound buffer, implemented as an std::span,
           meaning, modifications to the frame, are modifying the underlying buffer. */
        RustyAudio::Frame soundFrame = soundBuffer.at(frame);
        soundFrame = integerSample;
    }

    std::int32_t* pExistingData = soundBuffer.data();

    ma_audio_buffer_config config = ma_audio_buffer_config_init(ma_format_s32, soundBuffer.channels(), soundBuffer.frames(), pExistingData, NULL);
            
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

    /*
    Start the sound after it's applied to the sound. Otherwise there could be a scenario where
    the very first part of it is read before the attachment to the effect is made.
    */
    ma_sound_start(&g_sound);


    printf("Press Enter to quit...");
    getchar();

    ma_sound_uninit(&g_sound);
    ma_audio_buffer_uninit(&audioBuffer);
    ma_engine_uninit(&g_engine);

    return 0;
}