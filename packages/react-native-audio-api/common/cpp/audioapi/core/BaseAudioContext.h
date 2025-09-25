#pragma once

#include <audioapi/core/types/ContextState.h>
#include <audioapi/core/types/OscillatorType.h>


#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <complex>
#include <cstddef>
#include <cassert>

namespace audioapi {

class AudioBus;
class GainNode;
class AudioBuffer;
class PeriodicWave;
class OscillatorNode;
class StereoPannerNode;
class AudioNodeManager;
class BiquadFilterNode;
class AudioDestinationNode;
class AudioBufferSourceNode;
class AudioBufferQueueSourceNode;
class AudioDecoder;
class AnalyserNode;
class AudioEventHandlerRegistry;
class IAudioEventHandlerRegistry;
class RecorderAdapterNode;
class StreamerNode;

class BaseAudioContext {
 public:
  explicit BaseAudioContext(const std::shared_ptr<IAudioEventHandlerRegistry> &audioEventHandlerRegistry);
  virtual ~BaseAudioContext() = default;

  std::string getState();
  [[nodiscard]] float getSampleRate() const;
  [[nodiscard]] double getCurrentTime() const;
  [[nodiscard]] std::size_t getCurrentSampleFrame() const;
  std::shared_ptr<AudioDestinationNode> getDestination();

  std::shared_ptr<RecorderAdapterNode> createRecorderAdapter();
  std::shared_ptr<OscillatorNode> createOscillator();
  std::shared_ptr<StreamerNode> createStreamer();
  std::shared_ptr<GainNode> createGain();
  std::shared_ptr<StereoPannerNode> createStereoPanner();
  std::shared_ptr<BiquadFilterNode> createBiquadFilter();
  std::shared_ptr<AudioBufferSourceNode> createBufferSource(bool pitchCorrection);
  std::shared_ptr<AudioBufferQueueSourceNode> createBufferQueueSource(bool pitchCorrection);
  static std::shared_ptr<AudioBuffer>
  createBuffer(int numberOfChannels, size_t length, float sampleRate);
  std::shared_ptr<PeriodicWave> createPeriodicWave(
      const std::vector<std::complex<float>> &complexData,
      bool disableNormalization,
      int length);
  std::shared_ptr<AnalyserNode> createAnalyser();

  std::shared_ptr<AudioBuffer> decodeAudioDataSource(const std::string &path);
  std::shared_ptr<AudioBuffer> decodeAudioData(const void *data, size_t size);
  std::shared_ptr<AudioBuffer> decodeWithPCMInBase64(const std::string &data, float playbackSpeed);

  std::shared_ptr<PeriodicWave> getBasicWaveForm(OscillatorType type);
  [[nodiscard]] float getNyquistFrequency() const;
  AudioNodeManager *getNodeManager();

  [[nodiscard]] bool isRunning() const;
  [[nodiscard]] bool isSuspended() const;
  [[nodiscard]] bool isClosed() const;

 protected:
  static std::string toString(ContextState state);

  std::shared_ptr<AudioDestinationNode> destination_;
  // init in AudioContext or OfflineContext constructor
  std::shared_ptr<AudioDecoder> audioDecoder_ {};
  // init in AudioContext or OfflineContext constructor
  float sampleRate_ {};
  ContextState state_ = ContextState::RUNNING;
  std::shared_ptr<AudioNodeManager> nodeManager_;

 private:
  std::shared_ptr<PeriodicWave> cachedSineWave_ = nullptr;
  std::shared_ptr<PeriodicWave> cachedSquareWave_ = nullptr;
  std::shared_ptr<PeriodicWave> cachedSawtoothWave_ = nullptr;
  std::shared_ptr<PeriodicWave> cachedTriangleWave_ = nullptr;

  [[nodiscard]] virtual bool isDriverRunning() const = 0;

 public:
    std::shared_ptr<IAudioEventHandlerRegistry> audioEventHandlerRegistry_;
};

} // namespace audioapi
