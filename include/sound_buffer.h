#pragma once

#include <vector>
#include "sound_frame.h"
#include "sound_buffer_iterator.h"

namespace RustyAudio
{

// forward declaration to avoid the cyclical dependency
class SoundBufferIterator;

/* Container for all the data samples in a contiguous interleaved container for efficiency and compatibility with miniaudio API. */
class SoundBuffer
{
public:
    SoundBuffer(unsigned int sampleRate, unsigned int channels);

    void init(unsigned int milliseconds);

    const std::vector<std::int32_t>& buffer() const;

    std::vector<std::int32_t>& buffer();

    std::size_t size() const;

    std::size_t frames() const;

    unsigned int sampleRate() const;

    std::size_t channels() const;

    SoundFrame at(const std::size_t frameIndex);

    SoundBufferIterator begin();

    SoundBufferIterator end();

    std::int32_t* data();

private:
    unsigned int mSampleRate;
    std::size_t mChannels;
    std::vector<std::int32_t> mBuffer;
};

}