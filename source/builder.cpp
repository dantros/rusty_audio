#include "builder.h"
#include <cassert>

namespace RustyAudio
{

Builder::Builder()
{
}

Builder::~Builder()
{
}

Builder& Builder::append(WaveformVariant waveform)
{
    mDescriptors.push_back(std::move(waveform));
    return *this;
}

Builder& Builder::appendSinusoids(std::initializer_list<WaveformSinusoid> sinusoids)
{
    for (const auto& sinusoid : sinusoids)
        append(WaveformVariant{sinusoid});
    return *this;
}

Buffer Builder::generate(unsigned int sampleRate, unsigned int channels) const
{
    unsigned int totalDuration = 0;
    for (const auto& descriptor : mDescriptors)
        totalDuration += static_cast<unsigned int>(
            std::visit([](const auto& waveform) { return waveform.duration(); }, descriptor));

    RustyAudio::Buffer soundBuffer;
    soundBuffer.init(sampleRate, channels, totalDuration);

    std::size_t waveformIndex = 0;
    float waveformStartTime = 0.0f;

    for (std::size_t frame = 0; frame < soundBuffer.frames(); ++frame)
    {
        assert(waveformIndex < mDescriptors.size());

        const float milliseconds = soundBuffer.time(frame);
        const float localTime = milliseconds - waveformStartTime;

        const WaveformVariant& current = mDescriptors.at(waveformIndex);

        const std::int32_t sample = std::visit(
            [localTime](const auto& waveform) { return waveform(localTime); },
            current);

        soundBuffer.at(frame) = sample;

        const float waveformDuration = std::visit(
            [](const auto& waveform) { return waveform.duration(); },
            current);

        if (localTime >= waveformDuration)
        {
            waveformStartTime += waveformDuration;
            ++waveformIndex;
        }
    }

    return soundBuffer;
}

}
