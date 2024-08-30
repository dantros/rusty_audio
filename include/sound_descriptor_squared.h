#pragma once

#include "sound_descriptor_sinusoid.h"
#include <cstdint>
#include <cmath>
#include <numbers>
#include <limits>

namespace RustyAudio
{

class SoundDescriptorSquared : public SoundDescriptorSinusoid
{
public:
    SoundDescriptorSquared(unsigned int duration, float frequencyHz) :
        SoundDescriptorSinusoid(duration, frequencyHz)
    {}
    
    std::int32_t operator()(unsigned int milliseconds) const override
    {
        std::int32_t sinusoidValue = SoundDescriptorSinusoid::operator()(milliseconds);
        return sinusoidValue > 0 ? MAX_INT32 : -MAX_INT32;
    }
};

}