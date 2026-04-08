#pragma once

#include "waveform_sinusoid.h"
#include <cstdint>
#include <cmath>

#include "max_int32_audio.h"

namespace RustyAudio
{

// Pulse wave: like a square wave but with a configurable duty cycle.
// duty cycle 0.5 = square wave; 0.25 gives a thin, NES chip-style timbre.
// Shape per period: +1 for [0, dutyCycle), -1 for [dutyCycle, 1)
class WaveformPulse
{
public:
    WaveformPulse(float duration, float amplitude, float frequencyHz, float dutyCycle) :
        mBase(duration, amplitude, frequencyHz),
        mDutyCycle(dutyCycle)
    {}

    std::int32_t operator()(float milliseconds) const
    {
        const float phase  = std::fmod(mBase.frequency() * milliseconds / 1000.0f, 1.0f);
        const float sample = (phase < mDutyCycle) ? 1.0f : -1.0f;
        return static_cast<std::int32_t>(mBase.amplitude() * MAX_INT32_AS_FLOAT * sample);
    }

    float duration()  const { return mBase.duration(); }
    float amplitude() const { return mBase.amplitude(); }
    float frequency() const { return mBase.frequency(); }
    float dutyCycle() const { return mDutyCycle; }

private:
    WaveformSinusoid mBase;
    float mDutyCycle;
};

}
