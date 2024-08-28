#include "audio_buffer.h"
#include "audio_buffer_impl.h"

namespace RustyAudio
{

AudioBuffer::AudioBuffer()
{
    mAudioBufferImpl = std::make_unique<AudioBufferImpl>();
}

AudioBuffer::~AudioBuffer()
{
    
}

}