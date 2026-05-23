#pragma once

#include <numbers>
#include <limits>

namespace RustyAudio
{

namespace Internal
{
    // Slight headroom to avoid clipping artifacts at maximum amplitude
    // MAX >> 3 = MAX / 8 = 0.12 * MAX => 12% headroom
    static constexpr std::int32_t MAX_INT32 =
        std::numeric_limits<std::int32_t>::max() - (std::numeric_limits<std::int32_t>::max() >> 3);
}

static constexpr float MAX_INT32_AS_FLOAT = static_cast<float>(Internal::MAX_INT32);

}