#pragma once

#include <memory>

namespace RustyAudio
{

class AudioBuffer
{
public:
    AudioBuffer();
    ~AudioBuffer();

private:
    class AudioBufferImpl;
    std::unique_ptr<AudioBufferImpl> mAudioBufferImpl;
};

}