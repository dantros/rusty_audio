#pragma once

#include "frame.h"
#include <cstdint>
#include <cstddef>
#include <vector>

namespace RustyAudio
{

class Waveform
{
public:
    Waveform(unsigned int duration) :
        mDuration(duration)
    {}
    
    virtual std::int32_t operator()(unsigned int milliseconds) const { return 0; };

    unsigned int duration() const
    {
        return mDuration;
    }

protected:
    unsigned int mDuration;
};

}