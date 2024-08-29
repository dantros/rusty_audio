#pragma once

#include <cstdint>
#include <cstddef>

namespace RustyAudio
{

class SoundDescriptor
{
public:
    SoundDescriptor(unsigned int sampleRate, unsigned int channels);
    
    virtual std::int32_t operator()(float milliseconds) const;

private:
    unsigned int mSampleRate;
    std::size_t mChannels;
};

}