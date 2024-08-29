#pragma once

#include <memory>
#include "sound_buffer.h"

namespace RustyAudio
{

class SoundBuilder
{
public:
    SoundBuilder(const SoundBuffer& soundBuffer);
    ~SoundBuilder();

    void add();
    SoundBuffer generate();

private:

};

}