#include "audio_decoder.h"
#include <miniaudio.h>
#include <vector>

namespace RustyAudio
{

Buffer decodeAudioFromMemory(const void* data, std::size_t sizeInBytes)
{
    ma_decoder_config config = ma_decoder_config_init(ma_format_s32, 0, 0);
    ma_uint64 frameCount = 0;
    void* pFrames = nullptr;

    ma_result result = ma_decode_memory(data, sizeInBytes, &config, &frameCount, &pFrames);
    if (result != MA_SUCCESS)
        return {};

    auto* samples = static_cast<std::int32_t*>(pFrames);
    std::size_t totalSamples = static_cast<std::size_t>(frameCount) * config.channels;
    std::vector<std::int32_t> vec(samples, samples + totalSamples);
    ma_free(pFrames, nullptr);

    Buffer buffer;
    buffer.initFromData(config.sampleRate, config.channels, std::move(vec));
    return buffer;
}

Buffer decodeAudioFromFile(const char* filePath)
{
    ma_decoder_config config = ma_decoder_config_init(ma_format_s32, 0, 0);
    ma_uint64 frameCount = 0;
    void* pFrames = nullptr;

    ma_result result = ma_decode_file(filePath, &config, &frameCount, &pFrames);
    if (result != MA_SUCCESS)
        return {};

    auto* samples = static_cast<std::int32_t*>(pFrames);
    std::size_t totalSamples = static_cast<std::size_t>(frameCount) * config.channels;
    std::vector<std::int32_t> vec(samples, samples + totalSamples);
    ma_free(pFrames, nullptr);

    Buffer buffer;
    buffer.initFromData(config.sampleRate, config.channels, std::move(vec));
    return buffer;
}

}
