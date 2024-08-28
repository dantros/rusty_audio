
#include <sound_buffer.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <sound_buffer.h>

int main()
{
    constexpr unsigned int sampleRate = 1000;
    RustyAudio::SoundBuffer soundBuffer(sampleRate, 2);

    const unsigned int milliseconds = 10;
    soundBuffer.init(milliseconds);

    for (size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        /* a representation of time */
        const float t = static_cast<float>(frame) / sampleRate;

        /* sampling a sinusoid */
        const float sample = std::sin(500.0 * t);

        /* casting it to int32 */
        constexpr std::int32_t max = (std::numeric_limits<std::int32_t>::max)()*0.9; // artifacts if we reach the maximum value
        const float scaledSample = max * sample;
        std::int32_t integerSample = static_cast<std::int32_t>(scaledSample);

        RustyAudio::SoundFrame soundFrame = soundBuffer.at(frame);
        soundFrame = integerSample;
    }

    std::cout << "Hi!";
}