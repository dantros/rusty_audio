#pragma once

#include "buffer.h"
#include "waveform_variant.h"
#include "waveform_sinusoid.h"
#include <initializer_list>
#include <vector>

namespace RustyAudio
{

class Builder
{
public:
    Builder();
    ~Builder();
    Builder& append(WaveformVariant waveform);
    Builder& appendSinusoids(std::initializer_list<WaveformSinusoid> sinusoids);
    Buffer generate(unsigned int sampleRate, unsigned int channels) const;

private:
    std::vector<WaveformVariant> mDescriptors;
};

}
