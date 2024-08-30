#pragma once

#include "buffer_iterator.h"

namespace RustyAudio
{

BufferIterator::BufferIterator(Buffer* soundBuffer) :
    mSoundBufferPtr(soundBuffer), mCurrentIndex{0}
{}

BufferIterator::BufferIterator(Buffer* soundBuffer, std::size_t currentIndex) :
    mSoundBufferPtr(soundBuffer), mCurrentIndex{currentIndex}
{}

bool BufferIterator::operator!=(const BufferIterator& other) const
{
    return !(*this == other);
}

bool BufferIterator::operator==(const BufferIterator& other) const
{
    return mSoundBufferPtr == other.mSoundBufferPtr and
        mCurrentIndex == other.mCurrentIndex;
}

BufferIterator& BufferIterator::operator++()
{
    ++mCurrentIndex;
    return *this;
}

Frame BufferIterator::operator*()
{
    return {mSoundBufferPtr->buffer(), mCurrentIndex, mSoundBufferPtr->channels()};
}

}