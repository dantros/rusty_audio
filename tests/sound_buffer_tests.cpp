#include <gtest/gtest.h>
#include <rusty_audio.h>

// Demonstrate some basic assertions.
TEST(SoundDescriptorSinusoid01, BasicAssertions) {
  RustyAudio::WaveformSinusoid desc(1000, 600.0f);
  EXPECT_EQ(desc(100), 1843);
}
