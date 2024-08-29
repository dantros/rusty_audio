
#include <sound_buffer.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>
#include <sound_player.h>

int main()
{
    constexpr unsigned int sampleRate = 48000;
    RustyAudio::SoundBuffer soundBuffer(sampleRate, 2);

    const unsigned int milliseconds = 5000;
    soundBuffer.init(milliseconds);

    const float frequency_hz = 500.0f;
    const float frequency_rad = 2 * std::numbers::pi * frequency_hz;

    for (size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        /* a representation of time */
        const float t = static_cast<float>(frame) / sampleRate;

        /* sampling a sinusoid */
        const float sample = std::sin(frequency_rad * t);

        /* casting it to int32 */
        constexpr std::int32_t max = (std::numeric_limits<std::int32_t>::max)()*0.9; // artifacts if we reach the maximum value
        const float scaledSample = max * sample;
        std::int32_t integerSample = static_cast<std::int32_t>(scaledSample);

        RustyAudio::SoundFrame soundFrame = soundBuffer.at(frame);
        soundFrame = integerSample;
    }

    RustyAudio::SoundPlayer soundPlayer(soundBuffer);

    soundPlayer.play();

    std::cout << "Hi!";
    getchar();
}