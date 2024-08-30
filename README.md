# Rusty Audio

Basic C++ sound library that allows you to compose and play small sounds by specifying sinusoids directly on code.

The main goal is to quickly generate different sounds with only a few lines of code. No external audio files are required. You can use it to implement or prototype sounds for games as the sound reproduction happens in another thread. Under the hood, this is using the world famous [miniaudio](https://github.com/mackron/miniaudio).

A quick example:
```
    RustyAudio::Builder soundBuilder;
    soundBuilder.appendSinusoids({
        {200, 0.5, 600},
        {200, 0.5, 700},
        {200, 0.5, 600},
        {200, 0.5, 700},
        {200, 0.5, 600},
        {200, 0.5, 700},
        {200, 0.5, 600},
        {200, 0.5, 700},
        {200, 0.5, 600},
        {200, 0.5, 700}
    });

    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;
    RustyAudio::Buffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    RustyAudio::Player soundPlayer(soundBuffer);
    soundPlayer.play();
    
    std::cout << "Press enter to close";
    getchar(); 
```
The triplet `{200, 0.5, 600}` is describing a sinusoid wave with the signature `WaveformSinusoid(unsigned int milliseconds, float amplitude, float frequencyHz)`.

You can also create your own waveforms, and use them with the builder as follows
```
RustyAudio::Builder soundBuilder;
soundBuilder.append(std::make_unique<RustyAudio::WaveformSinusoid>(500, 0.2, 200.0f));
soundBuilder.append(std::make_unique<RustyAudio::WaveformSquared>(500, 0.4, 200.0f));
soundBuilder.append(std::make_unique<RustyAudio::WaveformSquared>(700, 0.4, 400.0f));

RustyAudio::Buffer soundBuffer = soundBuilder.generate(sampleRate, channels);
```
`RustyAudio::WaveformSinusoid` and `RustyAudio::WaveformSquared` are provided, but you can implement your own by inheriting `RustyAudio::Waveform`. This way, you can compose your sound little by little.

In `RustyAudio::Buffer` you can write any data you want, so the possibilities are wide open, you can generate music via code.
```
    constexpr unsigned int sampleRate = 48000;
    RustyAudio::Buffer soundBuffer(sampleRate, 2);

    const unsigned int milliseconds = 5000;
    soundBuffer.init(milliseconds);

    const float frequency_hz = 500.0f;
    const float frequency_rad = 2 * std::numbers::pi * frequency_hz;

    for (size_t frame = 0; frame < soundBuffer.frames() ; ++frame)
    {
        /* a representation of time */
        const float t = static_cast<float>(frame) / sampleRate;

        /* sampling a sinusoid */
        const float sample = std::sin(frequency_rad * t);

        /* casting it to int32 */
        constexpr std::int32_t max = (std::numeric_limits<std::int32_t>::max)()*0.9; // sound artifacts if we reach the maximum value
        const float scaledSample = max * sample;
        std::int32_t integerSample = static_cast<std::int32_t>(scaledSample);

        RustyAudio::Frame soundFrame = soundBuffer.at(frame);
        soundFrame = integerSample;
    }

    RustyAudio::Player soundPlayer(soundBuffer);

    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
```

## Setting up your project

You can use this repository as a git submodule
```
git submodule add https://github.com/dantros/rusty_audio.git third_party/rusty_audio
```
And then use `add_subdirectory` from your project's CMake file.
```
option(NOTHOFAGUS_INSTALL "Disabling installation of RustyAudio" OFF)
add_subdirectory("third_party/rusty_audio")

add_executable(rusty_audio_demo
    "source/rusty_audio_demo.cpp"
)
set_property(TARGET rusty_audio_demo PROPERTY CXX_STANDARD 20)
target_include_directories(rusty_audio_demo PRIVATE ${NOTHOFAGUS_INCLUDE})
target_link_libraries(rusty_audio_demo PRIVATE nothofagus)
```
There are other ways to work, choose whatever suits you best.

## Quick start

```
git clone https://github.com/dantros/rusty_audio.git
cd rusty_audio
git submodule update --init --recursive
cmake --presets ninja-release-examples
cd ../build_cmake/ninja-release-examples/
ninja
ninja install
cd ../install_cmake/ninja-release-example/
```
There you will find the rusty_audio static library and some demos.

## Dependencies

You should have [cmake](https://cmake.org/), [ninja](https://ninja-build.org/) and [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) (or another proper compiler) in your development environment.