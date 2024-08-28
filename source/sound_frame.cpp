#pragma once

#include "sound_frame.h"
#include <cassert>

namespace RustyAudio
{

SoundFrame::SoundFrame(std::vector<std::int32_t>& buffer, const std::size_t frame, const std::size_t channels) :
    mChannelSamples(buffer.begin() + (frame * channels), channels)
{}

const std::int32_t& SoundFrame::channel(const std::size_t i) const
{
    return mChannelSamples[i];
}

std::int32_t& SoundFrame::channel(const std::size_t i)
{
    return mChannelSamples[i];
}

std::size_t SoundFrame::size() const
{
    return mChannelSamples.size();
}

/* Convenience method to assign values to each channel of this frame */
SoundFrame& SoundFrame::operator=(std::initializer_list<std::int32_t> frame)
{
    assert(frame.size() == mChannelSamples.size());

    auto thisIt = mChannelSamples.begin();
    auto otherIt = frame.begin();

    while (otherIt != frame.end())
    {
        std::int32_t& oldData = *thisIt;
        const std::int32_t& newData = *otherIt;

        oldData = newData;

        ++thisIt;
        ++otherIt;
    }

    return *this;
}

}