#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <cmath>

namespace RustyAudio
{

// Sawtooth wave: linear ramp from -1 to +1 per period, then instant reset.
// Rich harmonic content — characteristic buzzy, bright timbre.
class WaveformSawtooth : public WaveformSinusoid
{
public:
    WaveformSawtooth(float duration, float amplitude, float frequencyHz) :
        WaveformSinusoid(duration, amplitude, frequencyHz)
    {}

    virtual std::int32_t operator()(float milliseconds) const override
    {
        // phase in [0, 1): 0 -> -1, 0.5 -> 0, 1 -> +1
        const float phase = std::fmod(frequency() * milliseconds / 1000.0f, 1.0f);
        const float sample = 2.0f * phase - 1.0f;

        return static_cast<std::int32_t>(amplitude() * MAX_INT32 * sample);
    }
};

}
