#pragma once

#include "buffer.h"
#include <concepts>

namespace RustyAudio
{

/**
 * @concept PlayBackend
 * @brief C++20 concept constraining audio playback backend types.
 *
 * Any type satisfying this concept can be used as the compile-time backend
 * for Player. Backends are selected via the RUSTY_AUDIO_PLAY_BACKEND CMake
 * option (MINIAUDIO or SDL3), which sets/unsets the RUSTY_AUDIO_BACKEND_SDL3 define.
 */
template<typename T>
concept PlayBackend = requires(T& backend, T const& constBackend, Buffer& buffer, bool looping)
{
    { T(buffer) };
    { backend.play()              } -> std::same_as<void>;
    { backend.pause()             } -> std::same_as<void>;
    { backend.stop()              } -> std::same_as<void>;
    { constBackend.isPlaying()    } -> std::same_as<bool>;
    { constBackend.isLooping()    } -> std::same_as<bool>;
    { backend.setLooping(looping) } -> std::same_as<void>;
};

} // namespace RustyAudio

// Include and alias the selected backend
#ifdef RUSTY_AUDIO_BACKEND_SDL3
    #include "sdl3_play_backend.h"
    namespace RustyAudio { using SelectedPlayBackend = Sdl3PlayBackend; }
#else
    #include "miniaudio_play_backend.h"
    namespace RustyAudio { using SelectedPlayBackend = MiniaudioPlayBackend; }
#endif

static_assert(
    RustyAudio::PlayBackend<RustyAudio::SelectedPlayBackend>,
    "Selected play backend does not satisfy the PlayBackend concept");
