#pragma once

#include <vector>
#include "frame.h"
#include "buffer_iterator.h"

namespace RustyAudio
{

// forward declaration to avoid the cyclical dependency
class SoundBufferIterator;

/* Container for all the data samples in a contiguous interleaved container for efficiency and compatibility with miniaudio API. */
class SoundBuffer
{
public:
    SoundBuffer(unsigned int sampleRate, unsigned int channels);

    /* Initialize a block of memory with value 0 to store the sound wave */
    void init(unsigned int milliseconds);

    /* Interface to the underlying std::vector */
    const std::vector<std::int32_t>& buffer() const;
    std::vector<std::int32_t>& buffer();

    /* getters */
    std::size_t size() const;
    std::size_t frames() const;
    unsigned int sampleRate() const;
    std::size_t channels() const;

    /* SoundFrame facade element access */
    SoundFrame at(const std::size_t frameIndex);

    /* Iterator interface*/
    SoundBufferIterator begin();
    SoundBufferIterator end();

    /* Interface to the underlying data */
    std::int32_t* data();

private:
    unsigned int mSampleRate;
    std::size_t mChannels;
    std::vector<std::int32_t> mBuffer;
};

}