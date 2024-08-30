#pragma once

#include "waveform.h"
#include <cstdint>
#include <cmath>
#include <numbers>
#include <limits>
#include <cassert>

namespace RustyAudio
{

class WaveformSinusoid : public Waveform
{
protected:
    // sound artifacts if we reach the maximum value
    static constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9; 
public:
    WaveformSinusoid(unsigned int duration, float amplitude, float frequencyHz) :
        Waveform(duration),
        mAmplitude(amplitude),
        mFrequencyRadMillis(2 * std::numbers::pi * frequencyHz / 1000)
    {
        assert(0 < amplitude and amplitude <= 1.0);
    }
    
    std::int32_t operator()(unsigned int milliseconds) const override
    {
        /* sampling a sinusoid */
        const float sample = mAmplitude * std::sin(mFrequencyRadMillis * milliseconds);

        /* scaling it and casting it to int32 */
        const float scaledSample = MAX_INT32 * sample;

        return static_cast<std::int32_t>(scaledSample);
    }

private:
    float mAmplitude;
    float mFrequencyRadMillis;
};

}