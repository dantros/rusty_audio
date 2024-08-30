
#include <rusty_audio.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>

int main()
{
    // TODO needs fixing.
    const unsigned int milliseconds = 5000;
    constexpr unsigned int sampleRate = 48000;

    RustyAudio::Buffer soundBuffer;
    soundBuffer.init(sampleRate, 2, milliseconds);

    const float frequencyHz = 500.0f;
    const float frequencyRadMillis = 2 * std::numbers::pi * frequencyHz / 1000;

    for (size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        /* a representation of time */
        const float timeMs = soundBuffer.time(frame);

        //std::cout << timeMs << " " << soundBuffer .duration() << std::endl;

        /* sampling a sinusoid */
        const float sample = std::sin(frequencyRadMillis * timeMs);

        /* casting it to int32 */
        constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9; // artifacts if we reach the maximum value
        const float scaledSample = MAX_INT32 * sample;
        std::int32_t integerSample = static_cast<std::int32_t>(scaledSample);

        RustyAudio::Frame soundFrame = soundBuffer.at(frame);
        soundFrame = integerSample;
    }

    RustyAudio::Player soundPlayer;
    soundPlayer.init(soundBuffer);

    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
}