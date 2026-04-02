
#include "sdl3_play_backend.h"
#include <SDL3/SDL.h>
#include <cstring>
#include <algorithm>
#include <cstdio>

namespace RustyAudio
{

static void audioCallback(void* userdata, SDL_AudioStream* stream, int additionalAmount, int /* totalAmount */)
{
    auto* backend = static_cast<Sdl3PlayBackend*>(userdata);
    backend->fillAudioData(stream, additionalAmount);
}

Sdl3PlayBackend::Sdl3PlayBackend(Buffer& soundBuffer)
    : mSoundBuffer(soundBuffer)
    , mStream(nullptr)
    , mPlaying(false)
    , mLooping(false)
    , mPlaybackOffset(0)
{
    if (!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO))
    {
        if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
        {
            printf("Failed to init SDL audio subsystem: %s\n", SDL_GetError());
            throw;
        }
    }

    SDL_AudioSpec spec;
    spec.format = SDL_AUDIO_S32;
    spec.channels = static_cast<int>(mSoundBuffer.channels());
    spec.freq = static_cast<int>(mSoundBuffer.sampleRate());

    mStream = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        &spec,
        audioCallback,
        this
    );

    if (!mStream)
    {
        printf("Failed to open SDL3 audio device stream: %s\n", SDL_GetError());
        throw;
    }
}

Sdl3PlayBackend::~Sdl3PlayBackend()
{
    if (mStream)
    {
        mPlaying.store(false, std::memory_order_release);

        // Guard against SDL already being shut down (e.g. if the window backend
        // called SDL_Quit before the interpreter destroys Player objects).
        if (SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO)
        {
            SDL_PauseAudioStreamDevice(mStream);
            SDL_ClearAudioStream(mStream);
            SDL_DestroyAudioStream(mStream);
        }
    }
}

void Sdl3PlayBackend::play()
{
    mPlaying.store(true, std::memory_order_release);
    SDL_ResumeAudioStreamDevice(mStream);
}

void Sdl3PlayBackend::pause()
{
    mPlaying.store(false, std::memory_order_release);
    SDL_PauseAudioStreamDevice(mStream);
}

void Sdl3PlayBackend::stop()
{
    mPlaying.store(false, std::memory_order_release);
    mPlaybackOffset.store(0, std::memory_order_release);
    SDL_PauseAudioStreamDevice(mStream);
    SDL_ClearAudioStream(mStream);
}

bool Sdl3PlayBackend::isPlaying() const
{
    return mPlaying.load(std::memory_order_acquire);
}

bool Sdl3PlayBackend::isLooping() const
{
    return mLooping.load(std::memory_order_acquire);
}

void Sdl3PlayBackend::setLooping(bool looping)
{
    mLooping.store(looping, std::memory_order_release);
}

void Sdl3PlayBackend::fillAudioData(SDL_AudioStream* stream, int additionalAmount)
{
    if (!mPlaying.load(std::memory_order_acquire))
    {
        return;
    }

    const auto* rawData = reinterpret_cast<const std::uint8_t*>(mSoundBuffer.data());
    const std::size_t totalBytes = mSoundBuffer.size() * sizeof(std::int32_t);
    int remaining = additionalAmount;

    while (remaining > 0)
    {
        std::size_t offset = mPlaybackOffset.load(std::memory_order_acquire);

        if (offset >= totalBytes)
        {
            if (mLooping.load(std::memory_order_acquire))
            {
                mPlaybackOffset.store(0, std::memory_order_release);
                continue;
            }
            else
            {
                mPlaying.store(false, std::memory_order_release);
                return;
            }
        }

        std::size_t available = totalBytes - offset;
        int chunk = static_cast<int>(std::min(static_cast<std::size_t>(remaining), available));
        SDL_PutAudioStreamData(stream, rawData + offset, chunk);
        mPlaybackOffset.store(offset + chunk, std::memory_order_release);
        remaining -= chunk;
    }
}

}
