#pragma once

#include "sound_descriptor.h"
#include <cstdint>
#include <cmath>
#include <numbers>
#include <limits>

namespace RustyAudio
{

class SoundDescriptorSinusoid : public SoundDescriptor
{
protected:
    // sound artifacts if we reach the maximum value
    static constexpr std::int32_t MAX_INT32 = (std::numeric_limits<std::int32_t>::max)()*0.9; 
public:
    SoundDescriptorSinusoid(unsigned int duration, float frequencyHz) :
        SoundDescriptor(duration),
        mFrequencyRadMillis(2 * std::numbers::pi * frequencyHz / 1000)
    {}
    
    std::int32_t operator()(unsigned int milliseconds) const override
    {
        /* sampling a sinusoid */
        const float sample = std::sin(mFrequencyRadMillis * milliseconds);

        /* scaling it and casting it to int32 */
        const float scaledSample = MAX_INT32 * sample;

        return static_cast<std::int32_t>(scaledSample);
    }

private:
    float mFrequencyRadMillis;
};

}