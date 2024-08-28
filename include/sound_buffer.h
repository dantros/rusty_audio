#pragma once

#include <vector>
#include <span>
#include <cassert>

namespace RustyAudio
{

/* Lightweight element to view the frame data contained in the sound buffer.
 * It is implemented as a span so we do not copy the underlying data. Henceforth, we can view it and modify it directly. */
class SoundFrame
{
public:
    SoundFrame(std::vector<std::int32_t>& buffer, const std::size_t frame, const std::size_t channels) :
        mChannelSamples(buffer.begin() + (frame * channels), channels)
    {}

    const std::int32_t& channel(const std::size_t i) const
    {
        return mChannelSamples[i];
    }

    std::int32_t& channel(const std::size_t i)
    {
        return mChannelSamples[i];
    }

    std::size_t size() const
    {
        mChannelSamples.size();
    }

    /* Convenience method to assign values to each channel of this frame */
    SoundFrame& operator=(std::initializer_list<std::int32_t> frame)
    {
        assert(frame.size() == mChannelSamples.size());

        auto thisIt = mChannelSamples.begin();
        auto otherIt = frame.begin();

        while (otherIt != frame.end())
        {
            std::int32_t& oldData = *thisIt;
            std::int32_t& newData = *otherIt;

            oldData = newData;

            ++thisIt;
            ++otherIt;
        }

        return *this;
    }

private:
    std::span<std::int32_t> mChannelSamples;
};

/* Basic iteratior to obtain SoundFrame elements from the SoundBuffer container */
class SoundBufferIterator
{
public:
    SoundBufferIterator(SoundBuffer* soundBuffer) :
        mSoundBufferPtr(soundBuffer), mCurrentIndex{0}
    {}

    SoundBufferIterator(SoundBuffer* soundBuffer, std::size_t currentIndex) :
        mSoundBufferPtr(soundBuffer), mCurrentIndex{currentIndex}
    {}

    bool operator!=(const SoundBufferIterator& other) const
    {
        return !(*this == other);
    }

    bool operator==(const SoundBufferIterator& other) const
    {
        return mSoundBufferPtr == other.mSoundBufferPtr and
            mCurrentIndex == other.mCurrentIndex;
    }

    SoundBufferIterator& operator++()
    {
        ++mCurrentIndex;
        return *this;
    }

    SoundFrame operator*()
    {
        return {mSoundBufferPtr->buffer(), mCurrentIndex, mSoundBufferPtr->channels()};
    }

private:
    SoundBuffer* mSoundBufferPtr;
    std::size_t mCurrentIndex;
};

/* Container for all the data samples in a contiguous interleaved container for efficiency and compatibility with miniaudio API. */
class SoundBuffer
{
public:
    SoundBuffer(unsigned int sampleRate, unsigned int channels);

    const std::vector<std::int32_t>& buffer() const
    {
        return mBuffer;
    }

    std::vector<std::int32_t>& buffer()
    {
        return mBuffer;
    }

    std::size_t size() const
    {
        return mBuffer.size();
    }

    std::size_t frames() const
    {
        return mBuffer.size() / mChannels;
    }

    std::size_t channels() const
    {
        return mChannels;
    }

    SoundFrame at(const std::size_t frameIndex) const
    {
        return {mBuffer, frameIndex, mChannels};
    }

    SoundFrame at(const std::size_t frameIndex)
    {
        return {mBuffer, frameIndex, mChannels};
    }

    SoundBufferIterator begin()
    {
        return SoundBufferIterator(this);
    }

    SoundBufferIterator end()
    {
        return SoundBufferIterator(this, size());
    }

    std::int32_t* data()
    {
        return mBuffer.data();
    }

private:
    unsigned int mSampleRate;
    unsigned int mChannels;
    std::vector<std::int32_t> mBuffer;
};

}