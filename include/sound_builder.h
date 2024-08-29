#pragma once

#include "sound_buffer.h"
#include "sound_descriptor.h"
#include <memory>
#include <vector>

namespace RustyAudio
{

class SoundBuilder
{
public:
    SoundBuilder();
    ~SoundBuilder();
    void enqueue(std::unique_ptr<SoundDescriptor> soundDescriptorPtr);
    SoundBuffer generate(unsigned int sampleRate, unsigned int channels);

private:
    std::vector<std::unique_ptr<SoundDescriptor>> mDescriptors;
};

}