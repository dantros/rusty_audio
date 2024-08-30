#pragma once

#include "buffer.h"
#include "waveform.h"
#include "waveform_sinusoid.h"
#include <memory>
#include <initializer_list>

namespace RustyAudio
{

class Builder
{
public:
    Builder();
    ~Builder();
    void append(std::unique_ptr<Waveform> soundDescriptorPtr);
    void appendSinusoids(std::initializer_list<WaveformSinusoid> sinusoids);
    Buffer generate(unsigned int sampleRate, unsigned int channels) const;

private:
    std::vector<std::unique_ptr<Waveform>> mDescriptors;
};

}