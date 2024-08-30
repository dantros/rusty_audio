
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

    for (int i = 0 ; i < 20; i++)
        soundBuilder.enqueue(std::make_unique<RustyAudio::WaveformSinusoid>(300, 0.8, 200.0f + i*50));

    RustyAudio::Buffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    RustyAudio::Player soundPlayer(soundBuffer);

    std::cout << "Press enter to play";
    getchar(); 
    soundPlayer.play();

    std::cout << "Press enter to pause";
    getchar();
    soundPlayer.pause();

    std::cout << "Press enter to continue";
    getchar();
    soundPlayer.play();

    std::cout << "Press enter to stop";
    getchar();
    soundPlayer.stop();

    std::cout << "Press enter to play again";
    getchar();
    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
    soundPlayer.stop();
}