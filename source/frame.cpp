#pragma once

#include "frame.h"
#include <cassert>

namespace RustyAudio
{

Frame::Frame(std::vector<std::int32_t>& buffer, const std::size_t frame, const std::size_t channels) :
    mChannelSamples(buffer.begin() + (frame * channels), channels)
{}

const std::int32_t& Frame::channel(const std::size_t i) const
{
    return mChannelSamples[i];
}

std::int32_t& Frame::channel(const std::size_t i)
{
    return mChannelSamples[i];
}

std::size_t Frame::size() const
{
    return mChannelSamples.size();
}

Frame& Frame::operator=(std::initializer_list<std::int32_t> values)
{
    assert(values.size() == mChannelSamples.size());

    auto thisIt = mChannelSamples.begin();
    auto otherIt = values.begin();

    while (otherIt != values.end())
    {
        std::int32_t& oldData = *thisIt;
        const std::int32_t& newData = *otherIt;

        oldData = newData;

        ++thisIt;
        ++otherIt;
    }

    return *this;
}

Frame& Frame::operator=(const std::int32_t value)
{
    auto thisIt = mChannelSamples.begin();

    while (thisIt != mChannelSamples.end())
    {
        std::int32_t& oldValue = *thisIt;
        oldValue = value;
        ++thisIt;
    }

    return *this;
}

}