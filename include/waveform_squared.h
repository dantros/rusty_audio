#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <cmath>
#include <numbers>
#include <limits>

namespace RustyAudio
{

class WaveformSquared : public WaveformSinusoid
{
public:
    WaveformSquared(unsigned int duration, float amplitude, float frequencyHz) :
        WaveformSinusoid(duration, amplitude, frequencyHz)
    {}
    
    std::int32_t operator()(unsigned int milliseconds) const override
    {
        std::int32_t sinusoidValue = WaveformSinusoid::operator()(milliseconds);
        return sinusoidValue > 0 ? MAX_INT32 : -MAX_INT32;
    }
};

}