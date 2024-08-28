#pragma once

#include "sound_buffer_iterator.h"

namespace RustyAudio
{

SoundBufferIterator::SoundBufferIterator(SoundBuffer* soundBuffer) :
    mSoundBufferPtr(soundBuffer), mCurrentIndex{0}
{}

SoundBufferIterator::SoundBufferIterator(SoundBuffer* soundBuffer, std::size_t currentIndex) :
    mSoundBufferPtr(soundBuffer), mCurrentIndex{currentIndex}
{}

bool SoundBufferIterator::operator!=(const SoundBufferIterator& other) const
{
    return !(*this == other);
}

bool SoundBufferIterator::operator==(const SoundBufferIterator& other) const
{
    return mSoundBufferPtr == other.mSoundBufferPtr and
        mCurrentIndex == other.mCurrentIndex;
}

SoundBufferIterator& SoundBufferIterator::operator++()
{
    ++mCurrentIndex;
    return *this;
}

SoundFrame SoundBufferIterator::operator*()
{
    return {mSoundBufferPtr->buffer(), mCurrentIndex, mSoundBufferPtr->channels()};
}

}