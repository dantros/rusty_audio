#pragma once

#include "buffer.h"
#include <SDL3/SDL_audio.h>
#include <atomic>
#include <cstddef>

namespace RustyAudio
{

class Sdl3PlayBackend
{
public:
    Sdl3PlayBackend(Buffer& soundBuffer);
    ~Sdl3PlayBackend();

    void play();
    void pause();
    void stop();
    bool isPlaying() const;
    bool isLooping() const;
    void setLooping(bool looping);

    // Internal — called from SDL audio callback thread
    void fillAudioData(SDL_AudioStream* stream, int additionalAmount);

private:
    Buffer& mSoundBuffer;
    SDL_AudioStream* mStream;
    std::atomic<bool> mPlaying;
    std::atomic<bool> mLooping;
    std::atomic<std::size_t> mPlaybackOffset;
};

}
