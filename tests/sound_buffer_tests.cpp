#include <catch2/catch_test_macros.hpp>
#include <rusty_audio.h>

TEST_CASE("SoundDescriptorSinusoid01 - BasicAssertions", "[waveform]") {
  RustyAudio::WaveformSinusoid desc(1000, 1.0f, 600.0f);
  REQUIRE(desc(100) == 1843);
}
