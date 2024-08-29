#pragma once

#include "sound_builder.h"
#include <cassert>

namespace RustyAudio
{

SoundBuilder::SoundBuilder()
{

}

SoundBuilder::~SoundBuilder()
{

}

void SoundBuilder::enqueue(std::unique_ptr<SoundDescriptor> soundDescriptorPtr)
{
    mDescriptors.push_back(std::move(soundDescriptorPtr));
}

SoundBuffer SoundBuilder::generate(unsigned int sampleRate, unsigned int channels)
{
    unsigned int totalDuration = 0;
    for (auto& descriptor : mDescriptors)
    {
        totalDuration += descriptor->duration();
    }

    RustyAudio::SoundBuffer soundBuffer(sampleRate, channels);
    soundBuffer.init(totalDuration);

    std::size_t currentDescriptorIndex = 0;
    unsigned int currentDescriptorStartTime = 0;

    SoundDescriptor* currentDescriptorPtr = mDescriptors.at(currentDescriptorIndex).get();
    assert(currentDescriptorPtr != nullptr);

    const float deltaTimeMilliseconds = static_cast<float>(totalDuration) / soundBuffer.frames();

    for (std::size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        const unsigned int milliseconds = frame * deltaTimeMilliseconds;
        const unsigned int localTime = milliseconds - currentDescriptorStartTime;

        SoundDescriptor& currentDescriptor = *currentDescriptorPtr;
        const std::int32_t sample = currentDescriptor(localTime);
        soundBuffer.at(frame) = sample;

        // if this is the last sample of the current descriptor, we need to switch to the next descriptor for the next sample.
        if (localTime == currentDescriptor.duration() - 1)
        {
            currentDescriptorStartTime += currentDescriptor.duration();
            ++currentDescriptorIndex;

            // maybe we are in the last descriptor, we dont want to go out of bounds.
            if (currentDescriptorIndex != mDescriptors.size())
            {
                currentDescriptorPtr = mDescriptors.at(currentDescriptorIndex).get();
                assert(currentDescriptorPtr != nullptr);

                
            }
        }
    }

    return soundBuffer;
}

}