#pragma once

#include <cmath>
#include <limits>

// https://webaudio.github.io/web-audio-api/

namespace audioapi {
// audio
static constexpr int RENDER_QUANTUM_SIZE = 128;
static constexpr size_t MAX_FFT_SIZE = 32768;

// general
static constexpr float MOST_POSITIVE_SINGLE_FLOAT = static_cast<float>(std::numeric_limits<float>::max());
static constexpr float MOST_NEGATIVE_SINGLE_FLOAT = static_cast<float>(std::numeric_limits<float>::lowest());
static float LOG2_MOST_POSITIVE_SINGLE_FLOAT = std::log2(MOST_POSITIVE_SINGLE_FLOAT);
static float LOG10_MOST_POSITIVE_SINGLE_FLOAT = std::log10(MOST_POSITIVE_SINGLE_FLOAT);
static constexpr float PI = static_cast<float>(M_PI);
} // namespace audioapi
