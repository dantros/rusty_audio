#pragma once

#include "buffer.h"
#include <cassert>

namespace RustyAudio
{

Buffer::Buffer() :
    mSampleRate{0},
    mChannels{0},
    mBuffer{}
{
}

void Buffer::init(unsigned int sampleRate, unsigned int channels, unsigned int milliseconds)
{
    mSampleRate = sampleRate;
    mChannels = channels;
    const unsigned int frames = (mSampleRate * milliseconds) / 1000;
    const std::size_t size = frames * mChannels;
    mBuffer.resize(size, 0);
}

const std::vector<std::int32_t>& Buffer::buffer() const
{
    return mBuffer;
}

std::vector<std::int32_t>& Buffer::buffer()
{
    return mBuffer;
}

std::size_t Buffer::size() const
{
    return mBuffer.size();
}

std::size_t Buffer::frames() const
{
    return mBuffer.size() / mChannels;
}

unsigned int Buffer::sampleRate() const
{
    return mSampleRate;
}

std::size_t Buffer::channels() const
{
    return mChannels;
}

Frame Buffer::at(const std::size_t frameIndex)
{
    assert(frameIndex < frames());
    return {mBuffer, frameIndex, mChannels};
}

BufferIterator Buffer::begin()
{
    return BufferIterator(this);
}

BufferIterator Buffer::end()
{
    return BufferIterator(this, size());
}

std::int32_t* Buffer::data()
{
    return mBuffer.data();
}

}