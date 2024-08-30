#pragma once

#include <vector>
#include <span>
#include <cstdint>

namespace RustyAudio
{

/* Lightweight element to view the frame data contained in the sound buffer.
 * It is implemented as an std::span so we do not copy the underlying data, but we still, we can view it and modify it directly. */
class SoundFrame
{
public:
    SoundFrame(std::vector<std::int32_t>& buffer, const std::size_t frame, const std::size_t channels);

    /* get a specific value from a channel */
    const std::int32_t& channel(const std::size_t i) const;
    std::int32_t& channel(const std::size_t i);

    std::size_t size() const;

    /* Convenience method to assign values to each channel of this frame */
    SoundFrame& operator=(std::initializer_list<std::int32_t> values);

    /* Convenience method to assign the same value to each channel of this frame */
    SoundFrame& operator=(const std::int32_t value);

private:
    std::span<std::int32_t> mChannelSamples;
};

}