#pragma once

#include "sound_buffer.h"

namespace RustyAudio
{

SoundBuffer::SoundBuffer(unsigned int sampleRate, unsigned int channels) :
    mSampleRate(sampleRate), mChannels(channels), mBuffer{}
{}

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

std::size_t SoundBuffer::channels() const
{
    return mChannels;
}

SoundFrame SoundBuffer::at(const std::size_t frameIndex)
{
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