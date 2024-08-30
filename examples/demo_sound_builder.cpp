
#include <rusty_audio.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>

int main()
{
    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;

    RustyAudio::SoundBuilder soundBuilder;
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(500, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(700, 400.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(500, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(700, 400.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(500, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(700, 400.0f));

    //for (int i = 0 ; i < 10; i++)
    //    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(1000, 200.0f + i*50));

    RustyAudio::SoundBuffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    RustyAudio::SoundPlayer soundPlayer(soundBuffer);

    soundPlayer.play();

    std::cout << "Press enter to listen again" << std::endl;
    getchar();

    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
}