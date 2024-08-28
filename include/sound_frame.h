#pragma once

#include <vector>
#include <span>

namespace RustyAudio
{

/* Lightweight element to view the frame data contained in the sound buffer.
 * It is implemented as a span so we do not copy the underlying data. Henceforth, we can view it and modify it directly. */
class SoundFrame
{
public:
    SoundFrame(std::vector<std::int32_t>& buffer, const std::size_t frame, const std::size_t channels);

    const std::int32_t& channel(const std::size_t i) const;

    std::int32_t& channel(const std::size_t i);

    std::size_t size() const;

    /* Convenience method to assign values to each channel of this frame */
    SoundFrame& operator=(std::initializer_list<std::int32_t> frame);

private:
    std::span<std::int32_t> mChannelSamples;
};

}