#pragma once

#include "sound_buffer.h"
#include <cassert>

namespace RustyAudio
{

SoundBuffer::SoundBuffer(unsigned int sampleRate, unsigned int channels) :
    mSampleRate(sampleRate), mChannels(channels), mBuffer()
{}

void SoundBuffer::init(unsigned int milliseconds)
{
    const unsigned int frames = (mSampleRate * milliseconds) / 1000;
    const std::size_t size = frames * mChannels;
    mBuffer.resize(size, 0);
}

const std::vector<std::int32_t>& SoundBuffer::buffer() const
{
    return mBuffer;
}

std::vector<std::int32_t>& SoundBuffer::buffer()
{
    return mBuffer;
}

std::size_t SoundBuffer::size() const
{
    return mBuffer.size();
}

std::size_t SoundBuffer::frames() const
{
    return mBuffer.size() / mChannels;
}

unsigned int SoundBuffer::sampleRate() const
{
    return mSampleRate;
}

std::size_t SoundBuffer::channels() const
{
    return mChannels;
}

SoundFrame SoundBuffer::at(const std::size_t frameIndex)
{
    assert(frameIndex < frames());
    return {mBuffer, frameIndex, mChannels};
}

SoundBufferIterator SoundBuffer::begin()
{
    return SoundBufferIterator(this);
}

SoundBufferIterator SoundBuffer::end()
{
    return SoundBufferIterator(this, size());
}

std::int32_t* SoundBuffer::data()
{
    return mBuffer.data();
}

}