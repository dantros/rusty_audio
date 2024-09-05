
#include <rusty_audio.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>

int main()
{
    constexpr unsigned int durationMs = 5000;
    constexpr float amplitude = 0.5;
    constexpr float frequencyHz = 600.0f;

    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;

    RustyAudio::Buffer soundBuffer;
    soundBuffer.init(sampleRate, channels, durationMs);
    
    const float frequencyRadMillis = 2 * std::numbers::pi * frequencyHz / 1000;

    for (size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        /* A representation of time */
        const float timeMs = soundBuffer.time(frame);

        /* Sampling a sinusoid */
        const float sample = amplitude * std::sin(frequencyRadMillis * timeMs);

        /* Casting it to int32 */
        constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9; // sound artifacts if we reach the maximum value
        const float scaledSample = MAX_INT32 * sample;
        std::int32_t integerSample = static_cast<std::int32_t>(scaledSample);

        /* A Frame is a convenient facade of the sound buffer, implemented as an std::span,
           meaning, modifications to the frame, are modifying the underlying buffer. */
        RustyAudio::Frame soundFrame = soundBuffer.at(frame);
        soundFrame = integerSample;
    }

    RustyAudio::Player soundPlayer;
    soundPlayer.init(soundBuffer);

    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
}