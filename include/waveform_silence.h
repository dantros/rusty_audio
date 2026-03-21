#pragma once

#include "waveform.h"
#include <cstdint>

namespace RustyAudio
{

class WaveformSilence : public Waveform
{
public:
    WaveformSilence(float duration) :
        Waveform(duration)
    {}

    virtual std::int32_t operator()(float milliseconds) const override
    {
        return 0;
    }
};

}
