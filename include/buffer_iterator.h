#pragma once

#include "frame.h"
#include "buffer.h"

namespace RustyAudio
{

class Buffer;

/* Basic iteratior to obtain SoundFrame elements from the SoundBuffer container */
class BufferIterator
{
public:
    BufferIterator(Buffer* soundBuffer);
    BufferIterator(Buffer* soundBuffer, std::size_t currentIndex);

    bool operator!=(const BufferIterator& other) const;
    bool operator==(const BufferIterator& other) const;

    BufferIterator& operator++();
    Frame operator*();

private:
    Buffer* mSoundBufferPtr;
    std::size_t mCurrentIndex;
};

}