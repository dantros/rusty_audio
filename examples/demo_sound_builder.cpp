
#include <rusty_audio.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>

int main()
{
    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;

    RustyAudio::Builder soundBuilder;
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSinusoid>(500, 0.2, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSinusoid>(700, 0.2, 400.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSinusoid>(500, 0.4, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSinusoid>(700, 0.4, 400.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSquared>(500, 0.6, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSquared>(700, 0.6, 400.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSquared>(500, 0.8, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSquared>(700, 0.8, 400.0f));

    //for (int i = 0 ; i < 10; i++)
    //    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(1000, 200.0f + i*50));

    RustyAudio::Buffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    RustyAudio::Player soundPlayer(soundBuffer);

    soundPlayer.play();

    std::cout << "Press enter to listen again" << std::endl;
    getchar();

    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
}