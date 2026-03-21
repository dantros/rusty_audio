#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <cmath>

namespace RustyAudio
{

// Triangle wave: linear rise from 0 to peak, fall through zero to trough, back to 0.
// Waveform shape per period: 0 -> +1 -> 0 -> -1 -> 0
class WaveformTriangle : public WaveformSinusoid
{
public:
    WaveformTriangle(float duration, float amplitude, float frequencyHz) :
        WaveformSinusoid(duration, amplitude, frequencyHz)
    {}

    virtual std::int32_t operator()(float milliseconds) const override
    {
        const float phase = std::fmod(frequency() * milliseconds / 1000.0f, 1.0f);

        float sample;
        if (phase < 0.25f)
            sample = 4.0f * phase;
        else if (phase < 0.75f)
            sample = 2.0f - 4.0f * phase;
        else
            sample = 4.0f * phase - 4.0f;

        return static_cast<std::int32_t>(amplitude() * MAX_INT32 * sample);
    }
};

}
