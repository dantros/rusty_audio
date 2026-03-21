#pragma once

#include "waveform_sinusoid.h"
#include "waveform_squared.h"
#include "waveform_triangle.h"
#include "waveform_sawtooth.h"
#include "waveform_silence.h"
#include <variant>

namespace RustyAudio
{

using WaveformVariant = std::variant<
    WaveformSinusoid,
    WaveformTriangle,
    WaveformSawtooth,
    WaveformSquared,
    WaveformSilence
>;

}
