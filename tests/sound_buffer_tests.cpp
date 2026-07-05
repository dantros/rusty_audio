#include <catch2/catch_test_macros.hpp>
#include <rusty_audio.h>

TEST_CASE("SoundDescriptorSinusoid01 - BasicAssertions", "[waveform]") {
  RustyAudio::WaveformSinusoid desc(1000, 1.0f, 600.0f);
  REQUIRE(desc(100) == 1843);
}

TEST_CASE("EmptyBuffer - getters do not divide by zero", "[buffer]") {
  RustyAudio::Buffer buf;          // default: channels=0, sampleRate=0, empty
  REQUIRE(buf.size()     == 0);
  REQUIRE(buf.frames()   == 0);    // pre-fix: SIGFPE (size / channels, channels==0)
  REQUIRE(buf.duration() == 0);    // pre-fix: SIGFPE (frames*1000 / sampleRate)
  REQUIRE(buf.time(0)    == 0.0f);
}
