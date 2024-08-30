#pragma once

#include "sound_buffer.h"
#include "waveform.h"
#include <memory>
#include <vector>

namespace RustyAudio
{

class SoundBuilder
{
public:
    SoundBuilder();
    ~SoundBuilder();
    void enqueue(std::unique_ptr<Waveform> soundDescriptorPtr);
    SoundBuffer generate(unsigned int sampleRate, unsigned int channels);

private:
    std::vector<std::unique_ptr<Waveform>> mDescriptors;
};

}