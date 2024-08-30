#pragma once

#include "buffer.h"
#include "waveform.h"
#include <memory>
#include <vector>

namespace RustyAudio
{

class Builder
{
public:
    Builder();
    ~Builder();
    void enqueue(std::unique_ptr<Waveform> soundDescriptorPtr);
    Buffer generate(unsigned int sampleRate, unsigned int channels);

private:
    std::vector<std::unique_ptr<Waveform>> mDescriptors;
};

}