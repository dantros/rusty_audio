#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <cmath>

#include "max_int32_audio.h"

namespace RustyAudio
{

// Sawtooth wave: linear ramp from -1 to +1 per period, then instant reset.
// Rich harmonic content — characteristic buzzy, bright timbre.
class WaveformSawtooth
{
    static constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9;

    WaveformSinusoid mBase;

public:
    WaveformSawtooth(float duration, float amplitude, float frequencyHz) :
        mBase(duration, amplitude, frequencyHz)
    {}

    std::int32_t operator()(float milliseconds) const
    {
        // phase in [0, 1): 0 -> -1, 0.5 -> 0, 1 -> +1
        const float phase = std::fmod(mBase.frequency() * milliseconds / 1000.0f, 1.0f);
        const float sample = 2.0f * phase - 1.0f;
        return static_cast<std::int32_t>(mBase.amplitude() * MAX_INT32_AS_FLOAT * sample);
    }

    float duration()  const { return mBase.duration(); }
    float amplitude() const { return mBase.amplitude(); }
    float frequency() const { return mBase.frequency(); }
};

}
