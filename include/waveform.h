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
    Waveform(float duration) :
        mDuration(duration)
    {}
    
    virtual std::int32_t operator()(float milliseconds) const { return 0.0f; };

    float duration() const
    {
        return mDuration;
    }

protected:
    float mDuration;
};

}