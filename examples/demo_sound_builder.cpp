
#include <sound_buffer.h>
#include <sound_player.h>
#include <sound_builder.h>
#include <sound_descriptor_sinusoid.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <numbers>

int main()
{
    RustyAudio::SoundDescriptorSinusoid desc(1000, 600.0f);
    std::cout << desc(100) << std::endl;

    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;

    RustyAudio::SoundBuilder soundBuilder;
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(2500, 200.0f));
    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(2500, 400.0f));

    //for (int i = 0 ; i < 10; i++)
    //    soundBuilder.enqueue(std::make_unique<RustyAudio::SoundDescriptorSinusoid>(1000, 200.0f + i*50));

    RustyAudio::SoundBuffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    RustyAudio::SoundPlayer soundPlayer(soundBuffer);

    soundPlayer.play();

    std::cout << "Hi!";
    getchar();
}