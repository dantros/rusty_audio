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
        const float sinusoidValue = std::sin(mFrequencyRadMillis * milliseconds);
        const float amplitude =  sinusoidValue > 0 ? mAmplitude : -mAmplitude;
        return MAX_INT32 * amplitude;
    }
};

}