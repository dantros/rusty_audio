# RustyAudio

A C++20 static library for generating and playing simple audio waves composed from sinusoids. Built on top of [miniaudio](https://miniaud.io/).

## Build

```cmake
add_subdirectory("third_party/rusty_audio")

target_include_directories(your_target PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(your_target PRIVATE rusty_audio)
```

CMake variables exported to the parent scope:
- `RUSTY_AUDIO_INCLUDE` — path to `include/`
- `MINIAUDIO_INCLUDE` — path to `third_party/miniaudio/`

CMake options:
- `RUSTY_AUDIO_BUILD_EXAMPLES` (OFF) — build the demo executables
- `RUSTY_AUDIO_BUILD_TESTS` (OFF) — build googletest suite
- `RUSTY_AUDIO_INSTALL` (ON) — install the static library

Single include: `#include <rusty_audio.h>`

## Core Concepts

Audio data is stored as **interleaved 32-bit signed integer samples** (`std::int32_t`) in a `Buffer`. A `Frame` is a lightweight `std::span`-based facade over one time-point across all channels — modifications to a `Frame` directly mutate the `Buffer`. A `Builder` composes a sequence of `Waveform` objects and generates a `Buffer` from them. A `Player` takes a `Buffer` reference and drives playback via miniaudio.

## Classes

### `RustyAudio::Buffer`

Container for all PCM samples. Interleaved layout: `[ch0, ch1, ch0, ch1, ...]`.

```cpp
Buffer buf;
buf.init(sampleRate, channels, durationMs); // allocates, zero-fills

buf.frames()           // number of frames (time points)
buf.size()             // total samples = frames * channels
buf.sampleRate()       // Hz
buf.channels()         // channel count
buf.time(frameIndex)   // float — time in milliseconds for that frame
buf.duration()         // unsigned int — total milliseconds
buf.at(frameIndex)     // Frame facade (modifiable span into buffer)
buf.data()             // std::int32_t* — raw pointer, needed for miniaudio integration
buf.buffer()           // std::vector<std::int32_t>& — direct vector access
```

### `RustyAudio::Frame`

Facade over one frame (all channels at a single time point). Implemented as `std::span` — changes write through to the parent `Buffer`.

```cpp
Frame f = buf.at(i);
f = 1234567;           // assign same value to all channels (operator=(int32_t))
f = {1234567, 7654321}; // assign per-channel (operator=(initializer_list))
f.channel(0)           // read/write single channel
f.size()               // channel count
```

**Lifetime:** A `Frame` must not outlive the `Buffer` it came from.

### `RustyAudio::Waveform` (abstract base)

```cpp
Waveform(float durationMs)
waveform(float timeMs) -> std::int32_t  // virtual operator()
waveform.duration()                     // float milliseconds
```

### `RustyAudio::WaveformSinusoid : Waveform`

Sinusoidal wave. Amplitude must be in `(0.0, 1.0]`.

```cpp
WaveformSinusoid(float durationMs, float amplitude, float frequencyHz)
sinusoid.amplitude()   // float
sinusoid.frequency()   // float Hz
```

Internally scales to `MAX_INT32 * 0.9` to avoid clipping artifacts.

### `RustyAudio::WaveformSquared : WaveformSinusoid`

Square wave — same constructor as `WaveformSinusoid`, output is binary `±MAX_INT32`.

```cpp
WaveformSquared(float durationMs, float amplitude, float frequencyHz)
```

### `RustyAudio::WaveformSilence : Waveform`

Silent gap — always returns 0. Useful as a rest between notes in a `Builder` sequence.

```cpp
WaveformSilence(float durationMs)
```

### `RustyAudio::WaveformTriangle : WaveformSinusoid`

Triangle wave — linear rise/fall shape per period. Mellow analog character; odd harmonics
that decay faster than a square wave (`1/n²` instead of `1/n`).

```cpp
WaveformTriangle(float durationMs, float amplitude, float frequencyHz)
// Shape per period: 0 → +1 → 0 → -1 → 0
```

### `RustyAudio::WaveformSawtooth : WaveformSinusoid`

Sawtooth wave — linear ramp from -1 to +1 per period then instant reset. Bright, buzzy
timbre; all harmonics present (`1/n` rolloff like a square, but both even and odd).

```cpp
WaveformSawtooth(float durationMs, float amplitude, float frequencyHz)
// Shape per period: -1 → +1 (instant reset at boundary)
```

### `RustyAudio::Builder`

Composes waveforms sequentially and generates a buffer. Waveforms are played one after another (not mixed/overlapped).

```cpp
Builder builder;

// Append individual waveforms (takes ownership via unique_ptr)
builder.append(std::make_unique<WaveformSinusoid>(500, 0.5, 440.0f));
builder.append(std::make_unique<WaveformSquared>(300, 0.8, 220.0f));

// Append multiple sinusoids at once
builder.appendSinusoids({
    {200, 0.5, 600},   // {durationMs, amplitude, frequencyHz}
    {200, 0.5, 700},
});

Buffer buf = builder.generate(sampleRate, channels);
```

### `RustyAudio::Player`

Wraps miniaudio playback. Uses Pimpl — `PlayerImpl` is internal.

```cpp
Player player;
player.init(buf);        // buf must outlive player
player.play();
player.pause();
player.stop();           // resets position to start
player.isPlaying()       // bool
player.isLooping()       // bool
player.setLooping(true);
```

**Ownership:** `init(Buffer&)` stores a reference — the `Buffer` must remain alive for the entire lifetime of the `Player`.

### `RustyAudio::Note` (struct)

Convenience data struct. Not used by `Builder` directly.

```cpp
struct Note {
    int milliseconds;
    double amplitude;
    double frecuency;   // note: typo in original spelling
};
```

## Usage Patterns

### Manual buffer fill (demo_buffer.cpp)

```cpp
Buffer buf;
buf.init(48000, 2, 5000);

const float freqRad = 2 * std::numbers::pi * 600.0f / 1000;
constexpr std::int32_t MAX = std::numeric_limits<std::int32_t>::max() * 0.9;

for (size_t i = 0; i < buf.frames(); ++i)
{
    float sample = 0.5f * std::sin(freqRad * buf.time(i));
    buf.at(i) = static_cast<std::int32_t>(MAX * sample);
}

Player player;
player.init(buf);
player.play();
```

### Builder (demo_builder.cpp)

```cpp
Builder builder;
builder.append(std::make_unique<WaveformSinusoid>(500, 0.2, 200.0f));
builder.append(std::make_unique<WaveformSquared>(700, 0.6, 400.0f));

Buffer buf = builder.generate(48000, 2);

Player player;
player.init(buf);
player.play();
```

### appendSinusoids shorthand (demo_builder2.cpp)

```cpp
Builder builder;
builder.appendSinusoids({
    {200, 0.5, 600},
    {200, 0.5, 700},
});
Buffer buf = builder.generate(48000, 2);
```

### miniaudio integration (demo_miniaudio.cpp)

Use `buf.data()` and `buf.frames()` to feed a `ma_audio_buffer`:

```cpp
ma_audio_buffer_config cfg = ma_audio_buffer_config_init(
    ma_format_s32, buf.channels(), buf.frames(), buf.data(), NULL);
ma_audio_buffer_init(&cfg, &audioBuffer);
ma_sound_init_from_data_source(&engine, &audioBuffer, 0, NULL, &sound);
```

## Key Constraints

- All samples are `std::int32_t`. Scale by `std::numeric_limits<std::int32_t>::max() * 0.9` to avoid clipping artifacts at maximum amplitude.
- `Frame` is an `std::span` — it does **not** own data. Never store a `Frame` beyond the current scope.
- `Player::init` takes `Buffer&` — the buffer must outlive the player. If the buffer may be destroyed before the player, copy the buffer first.
- `Builder::append` takes `std::unique_ptr<Waveform>` — the builder takes ownership.
- `appendSinusoids` accepts `std::initializer_list<WaveformSinusoid>` — waveforms are copied in (no unique_ptr needed here).
- C++20 required (`std::numbers::pi`, `std::span`).
