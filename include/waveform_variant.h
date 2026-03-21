#pragma once

#include "waveform_sinusoid.h"
#include "waveform_squared.h"
#include "waveform_triangle.h"
#include "waveform_sawtooth.h"
#include "waveform_silence.h"
#include "waveform_pulse.h"
#include "waveform_noise.h"
#include "waveform_chirp.h"
#include <variant>

namespace RustyAudio
{

using WaveformVariant = std::variant<
    WaveformSinusoid,
    WaveformTriangle,
    WaveformSawtooth,
    WaveformSquared,
    WaveformSilence,
    WaveformPulse,
    WaveformNoise,
    WaveformChirp
>;

}
