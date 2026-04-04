#include "audio_decoder.h"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_iostream.h>
#include <vector>

namespace RustyAudio
{

static Buffer decodeFromSdlAudio(const SDL_AudioSpec& loadedSpec,
                                 Uint8* audioData, Uint32 audioLen)
{
    SDL_AudioSpec targetSpec;
    targetSpec.format   = SDL_AUDIO_S32;
    targetSpec.channels = loadedSpec.channels;
    targetSpec.freq     = loadedSpec.freq;

    Uint8* convertedData = nullptr;
    int convertedLen = 0;

    if (!SDL_ConvertAudioSamples(&loadedSpec, audioData, static_cast<int>(audioLen),
                                 &targetSpec, &convertedData, &convertedLen))
    {
        return {};
    }

    auto* samples = reinterpret_cast<std::int32_t*>(convertedData);
    std::size_t totalSamples = static_cast<std::size_t>(convertedLen) / sizeof(std::int32_t);
    std::vector<std::int32_t> vec(samples, samples + totalSamples);
    SDL_free(convertedData);

    Buffer buffer;
    buffer.initFromData(static_cast<unsigned int>(targetSpec.freq),
                        static_cast<unsigned int>(targetSpec.channels),
                        std::move(vec));
    return buffer;
}

Buffer decodeAudioFromMemory(const void* data, std::size_t sizeInBytes)
{
    SDL_IOStream* io = SDL_IOFromConstMem(data, sizeInBytes);
    if (!io)
        return {};

    SDL_AudioSpec loadedSpec;
    Uint8* audioData = nullptr;
    Uint32 audioLen = 0;

    if (!SDL_LoadWAV_IO(io, true, &loadedSpec, &audioData, &audioLen))
        return {};

    Buffer result = decodeFromSdlAudio(loadedSpec, audioData, audioLen);
    SDL_free(audioData);
    return result;
}

Buffer decodeAudioFromFile(const char* filePath)
{
    SDL_AudioSpec loadedSpec;
    Uint8* audioData = nullptr;
    Uint32 audioLen = 0;

    if (!SDL_LoadWAV(filePath, &loadedSpec, &audioData, &audioLen))
        return {};

    Buffer result = decodeFromSdlAudio(loadedSpec, audioData, audioLen);
    SDL_free(audioData);
    return result;
}

}
