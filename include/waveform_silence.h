#pragma once

#include <cstdint>

namespace RustyAudio
{

class WaveformSilence
{
    float mDuration;

public:
    WaveformSilence(float duration) :
        mDuration(duration)
    {}

    std::int32_t operator()(float /*milliseconds*/) const
    {
        return 0;
    }

    float duration() const { return mDuration; }
};

}
