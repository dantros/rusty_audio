#pragma once

#include "builder.h"
#include <cassert>

namespace RustyAudio
{

Builder::Builder()
{

}

Builder::~Builder()
{

}

void Builder::append(std::unique_ptr<Waveform> soundDescriptorPtr)
{
    mDescriptors.push_back(std::move(soundDescriptorPtr));
}

void Builder::appendSinusoids(std::initializer_list<WaveformSinusoid> sinusoids)
{
    for (const auto& sinusoid : sinusoids)
    {
        append(std::make_unique<WaveformSinusoid>(
            sinusoid.duration(),
            sinusoid.amplitude(),
            sinusoid.frequency()
        ));
    }
}

Buffer Builder::generate(unsigned int sampleRate, unsigned int channels) const
{
    unsigned int totalDuration = 0;
    for (auto& descriptor : mDescriptors)
    {
        totalDuration += descriptor->duration();
    }

    RustyAudio::Buffer soundBuffer;
    soundBuffer.init(sampleRate, channels, totalDuration);

    std::size_t waveformIndex = 0;
    unsigned int waveformStartTime = 0;

    Waveform* waveformPtr = mDescriptors.at(waveformIndex).get();
    assert(waveformPtr != nullptr);

    const float deltaTimeMilliseconds = static_cast<float>(totalDuration) / soundBuffer.frames();

    for (std::size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        const unsigned int milliseconds = frame * deltaTimeMilliseconds;
        const unsigned int localTime = milliseconds - waveformStartTime;

        Waveform& waveform = *waveformPtr;
        const std::int32_t sample = waveform(localTime);
        soundBuffer.at(frame) = sample;

        // if this is the last sample of the current descriptor, we need to switch to the next descriptor for the next sample.
        if (localTime == waveform.duration() - 1)
        {
            waveformStartTime += waveform.duration();
            ++waveformIndex;

            // maybe we are in the last descriptor, we dont want to go out of bounds.
            if (waveformIndex != mDescriptors.size())
            {
                waveformPtr = mDescriptors.at(waveformIndex).get();
                assert(waveformPtr != nullptr);

                
            }
        }
    }

    return soundBuffer;
}

}