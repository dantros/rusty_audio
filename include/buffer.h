#pragma once

#include <vector>
#include "frame.h"
#include "buffer_iterator.h"

namespace RustyAudio
{

// forward declaration to avoid the cyclical dependency
class BufferIterator;

/* Container for all the data samples in a contiguous interleaved container for efficiency and compatibility with miniaudio API. */
class Buffer
{
public:
    Buffer();

    /* Initialize a block of memory with value 0 to store the sound wave */
    void init(unsigned int sampleRate, unsigned int channels, unsigned int milliseconds);

    /* Interface to the underlying std::vector */
    const std::vector<std::int32_t>& buffer() const;
    std::vector<std::int32_t>& buffer();

    /* Getters */
    std::size_t size() const;
    std::size_t frames() const;
    unsigned int sampleRate() const;
    std::size_t channels() const;

    /* Time in milliseconds associated to a specific frame */
    float time(std::size_t frame) const;

    /* Total duration in milliseconds of this sound */
    unsigned int duration() const;

    /* SoundFrame facade element access */
    Frame at(const std::size_t frameIndex);

    /* Iterator interface*/
    BufferIterator begin();
    BufferIterator end();

    /* Interface to the underlying data */
    std::int32_t* data();

private:
    unsigned int mSampleRate;
    std::size_t mChannels;
    std::vector<std::int32_t> mBuffer;
};

}