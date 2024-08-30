#pragma once

#include "frame.h"
#include "buffer.h"

namespace RustyAudio
{

class SoundBuffer;

/* Basic iteratior to obtain SoundFrame elements from the SoundBuffer container */
class SoundBufferIterator
{
public:
    SoundBufferIterator(SoundBuffer* soundBuffer);
    SoundBufferIterator(SoundBuffer* soundBuffer, std::size_t currentIndex);

    bool operator!=(const SoundBufferIterator& other) const;
    bool operator==(const SoundBufferIterator& other) const;

    SoundBufferIterator& operator++();
    SoundFrame operator*();

private:
    SoundBuffer* mSoundBufferPtr;
    std::size_t mCurrentIndex;
};

}