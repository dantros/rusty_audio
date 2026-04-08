#pragma once

#include <cstdint>
#include <cmath>
#include <numbers>

#include "max_int32_audio.h"

namespace RustyAudio
{

// Chirp (frequency sweep): frequency glides linearly from startFrequency to endFrequency
// over the full duration. Phase is computed by analytically integrating the instantaneous
// frequency so the sine wave is always continuous with no discontinuities.
//
// Instantaneous frequency: f(t) = f0 + (f1 - f0) * t / T
// Phase: 2π/1000 * (f0*t + (f1-f0)*t²/(2*T))   [t and T in milliseconds]
class WaveformChirp
{
public:
    WaveformChirp(float duration, float amplitude, float startFrequencyHz, float endFrequencyHz) :
        mDuration(duration),
        mAmplitude(amplitude),
        mStartFrequency(startFrequencyHz),
        mEndFrequency(endFrequencyHz)
    {}

    std::int32_t operator()(float milliseconds) const
    {
        const float t  = milliseconds;
        const float T  = mDuration;
        const float f0 = mStartFrequency;
        const float f1 = mEndFrequency;
        const float phase = 2.0f * std::numbers::pi / 1000.0f
                            * (f0 * t + (f1 - f0) * t * t / (2.0f * T));
        const float sample = mAmplitude * std::sin(phase);
        return static_cast<std::int32_t>(MAX_INT32_AS_FLOAT * sample);
    }

    float duration()       const { return mDuration; }
    float amplitude()      const { return mAmplitude; }
    float startFrequency() const { return mStartFrequency; }
    float endFrequency()   const { return mEndFrequency; }

private:
    float mDuration;
    float mAmplitude;
    float mStartFrequency;
    float mEndFrequency;
};

}
