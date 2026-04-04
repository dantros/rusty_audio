#pragma once

#include "buffer.h"
#include <cstddef>

namespace RustyAudio
{

// Decode audio data (WAV/FLAC/MP3) from memory into a Buffer.
// Returns a default-constructed (empty) Buffer on failure.
Buffer decodeAudioFromMemory(const void* data, std::size_t sizeInBytes);

// Decode audio from a file path. Returns empty Buffer on failure.
Buffer decodeAudioFromFile(const char* filePath);

}
