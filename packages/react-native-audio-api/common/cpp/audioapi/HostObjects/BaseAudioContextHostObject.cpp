#include <audioapi/HostObjects/BaseAudioContextHostObject.h>

#include <audioapi/HostObjects/analysis/AnalyserNodeHostObject.h>
#include <audioapi/HostObjects/destinations/AudioDestinationNodeHostObject.h>
#include <audioapi/HostObjects/effects/BiquadFilterNodeHostObject.h>
#include <audioapi/HostObjects/effects/GainNodeHostObject.h>
#include <audioapi/HostObjects/effects/PeriodicWaveHostObject.h>
#include <audioapi/HostObjects/effects/StereoPannerNodeHostObject.h>
#include <audioapi/HostObjects/sources/AudioBufferHostObject.h>
#include <audioapi/HostObjects/sources/AudioBufferQueueSourceNodeHostObject.h>
#include <audioapi/HostObjects/sources/AudioBufferSourceNodeHostObject.h>
#include <audioapi/HostObjects/sources/OscillatorNodeHostObject.h>
#include <audioapi/HostObjects/sources/RecorderAdapterNodeHostObject.h>
#include <audioapi/HostObjects/sources/StreamerNodeHostObject.h>
#include <audioapi/core/BaseAudioContext.h>

namespace audioapi {

BaseAudioContextHostObject::BaseAudioContextHostObject(
    const std::shared_ptr<BaseAudioContext> &context,
    jsi::Runtime *runtime,
    const std::shared_ptr<react::CallInvoker> &callInvoker)
    : context_(context), callInvoker_(callInvoker) {
  promiseVendor_ = std::make_shared<PromiseVendor>(runtime, callInvoker);

  addGetters(
      JSI_EXPORT_PROPERTY_GETTER(BaseAudioContextHostObject, destination),
      JSI_EXPORT_PROPERTY_GETTER(BaseAudioContextHostObject, state),
      JSI_EXPORT_PROPERTY_GETTER(BaseAudioContextHostObject, sampleRate),
      JSI_EXPORT_PROPERTY_GETTER(BaseAudioContextHostObject, currentTime));

  addFunctions(
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createRecorderAdapter),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createOscillator),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createStreamer),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createGain),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createStereoPanner),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createBiquadFilter),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createBufferSource),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createBufferQueueSource),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createBuffer),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createPeriodicWave),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, createAnalyser),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, decodeAudioData),
      JSI_EXPORT_FUNCTION(BaseAudioContextHostObject, decodeAudioDataSource),
      JSI_EXPORT_FUNCTION(
          BaseAudioContextHostObject, decodePCMAudioDataInBase64));
}

JSI_PROPERTY_GETTER_IMPL(BaseAudioContextHostObject, destination) {
  auto destination = std::make_shared<AudioDestinationNodeHostObject>(
      context_->getDestination());
  return jsi::Object::createFromHostObject(runtime, destination);
}

JSI_PROPERTY_GETTER_IMPL(BaseAudioContextHostObject, state) {
  return jsi::String::createFromUtf8(runtime, context_->getState());
}

JSI_PROPERTY_GETTER_IMPL(BaseAudioContextHostObject, sampleRate) {
  return {context_->getSampleRate()};
}

JSI_PROPERTY_GETTER_IMPL(BaseAudioContextHostObject, currentTime) {
  return {context_->getCurrentTime()};
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createRecorderAdapter) {
  auto recorderAdapter = context_->createRecorderAdapter();
  auto recorderAdapterHostObject =
      std::make_shared<RecorderAdapterNodeHostObject>(recorderAdapter);
  return jsi::Object::createFromHostObject(runtime, recorderAdapterHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createOscillator) {
  auto oscillator = context_->createOscillator();
  auto oscillatorHostObject =
      std::make_shared<OscillatorNodeHostObject>(oscillator);
  return jsi::Object::createFromHostObject(runtime, oscillatorHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createStreamer) {
  auto streamer = context_->createStreamer();
  auto streamerHostObject = std::make_shared<StreamerNodeHostObject>(streamer);
  auto object = jsi::Object::createFromHostObject(runtime, streamerHostObject);
  object.setExternalMemoryPressure(
      runtime, StreamerNodeHostObject::getSizeInBytes());
  return object;
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createGain) {
  auto gain = context_->createGain();
  auto gainHostObject = std::make_shared<GainNodeHostObject>(gain);
  return jsi::Object::createFromHostObject(runtime, gainHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createStereoPanner) {
  auto stereoPanner = context_->createStereoPanner();
  auto stereoPannerHostObject =
      std::make_shared<StereoPannerNodeHostObject>(stereoPanner);
  return jsi::Object::createFromHostObject(runtime, stereoPannerHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createBiquadFilter) {
  auto biquadFilter = context_->createBiquadFilter();
  auto biquadFilterHostObject =
      std::make_shared<BiquadFilterNodeHostObject>(biquadFilter);
  return jsi::Object::createFromHostObject(runtime, biquadFilterHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createBufferSource) {
  auto pitchCorrection = args[0].asBool();
  auto bufferSource = context_->createBufferSource(pitchCorrection);
  auto bufferSourceHostObject =
      std::make_shared<AudioBufferSourceNodeHostObject>(bufferSource);
  return jsi::Object::createFromHostObject(runtime, bufferSourceHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createBufferQueueSource) {
  auto pitchCorrection = args[0].asBool();
  auto bufferSource = context_->createBufferQueueSource(pitchCorrection);
  auto bufferStreamSourceHostObject =
      std::make_shared<AudioBufferQueueSourceNodeHostObject>(bufferSource);
  return jsi::Object::createFromHostObject(
      runtime, bufferStreamSourceHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createBuffer) {
  auto numberOfChannels = static_cast<int>(args[0].getNumber());
  auto length = static_cast<size_t>(args[1].getNumber());
  auto sampleRate = static_cast<float>(args[2].getNumber());
  auto buffer =
      BaseAudioContext::createBuffer(numberOfChannels, length, sampleRate);
  auto bufferHostObject = std::make_shared<AudioBufferHostObject>(buffer);

  auto jsiObject = jsi::Object::createFromHostObject(runtime, bufferHostObject);
  jsiObject.setExternalMemoryPressure(
      runtime, bufferHostObject->getSizeInBytes());

  return jsiObject;
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createPeriodicWave) {
  auto arrayBufferReal = args[0]
                             .getObject(runtime)
                             .getPropertyAsObject(runtime, "buffer")
                             .getArrayBuffer(runtime);
  auto real = reinterpret_cast<float *>(arrayBufferReal.data(runtime));
  auto length = static_cast<int>(arrayBufferReal.size(runtime));

  auto arrayBufferImag = args[1]
                             .getObject(runtime)
                             .getPropertyAsObject(runtime, "buffer")
                             .getArrayBuffer(runtime);
  auto imag = reinterpret_cast<float *>(arrayBufferImag.data(runtime));

  auto disableNormalization = args[2].getBool();

  auto complexData = std::vector<std::complex<float>>(length);

  for (size_t i = 0; i < length; i++) {
    complexData[i] = std::complex<float>(
        static_cast<float>(real[i]), static_cast<float>(imag[i]));
  }

  auto periodicWave =
      context_->createPeriodicWave(complexData, disableNormalization, length);
  auto periodicWaveHostObject =
      std::make_shared<PeriodicWaveHostObject>(periodicWave);

  return jsi::Object::createFromHostObject(runtime, periodicWaveHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, createAnalyser) {
  auto analyser = context_->createAnalyser();
  auto analyserHostObject = std::make_shared<AnalyserNodeHostObject>(analyser);
  return jsi::Object::createFromHostObject(runtime, analyserHostObject);
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, decodeAudioDataSource) {
  auto sourcePath = args[0].getString(runtime).utf8(runtime);

  auto promise = promiseVendor_->createPromise(
      [this, sourcePath](std::shared_ptr<Promise> promise) {
        std::thread([this, sourcePath, promise = std::move(promise)]() {
          auto results = context_->decodeAudioDataSource(sourcePath);

          if (!results) {
            promise->reject("Failed to decode audio data source.");
            return;
          }

          auto audioBufferHostObject =
              std::make_shared<AudioBufferHostObject>(results);

          promise->resolve([audioBufferHostObject = std::move(
                                audioBufferHostObject)](jsi::Runtime &runtime) {
            auto jsiObject = jsi::Object::createFromHostObject(
                runtime, audioBufferHostObject);
            jsiObject.setExternalMemoryPressure(
                runtime, audioBufferHostObject->getSizeInBytes());
            return jsiObject;
          });
        }).detach();
      });

  return promise;
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, decodeAudioData) {
  auto arrayBuffer = args[0]
                         .getObject(runtime)
                         .getPropertyAsObject(runtime, "buffer")
                         .getArrayBuffer(runtime);
  auto data = arrayBuffer.data(runtime);
  auto size = static_cast<int>(arrayBuffer.size(runtime));

  auto promise = promiseVendor_->createPromise(
      [this, data, size](std::shared_ptr<Promise> promise) {
        std::thread([this, data, size, promise = std::move(promise)]() {
          auto results = context_->decodeAudioData(data, size);

          if (!results) {
            promise->reject("Failed to decode audio data source.");
            return;
          }

          auto audioBufferHostObject =
              std::make_shared<AudioBufferHostObject>(results);

          promise->resolve([audioBufferHostObject = std::move(
                                audioBufferHostObject)](jsi::Runtime &runtime) {
            auto jsiObject = jsi::Object::createFromHostObject(
                runtime, audioBufferHostObject);
            jsiObject.setExternalMemoryPressure(
                runtime, audioBufferHostObject->getSizeInBytes());
            return jsiObject;
          });
        }).detach();
      });

  return promise;
}

JSI_HOST_FUNCTION_IMPL(BaseAudioContextHostObject, decodePCMAudioDataInBase64) {
  auto b64 = args[0].getString(runtime).utf8(runtime);
  auto playbackSpeed = static_cast<float>(args[1].getNumber());

  auto promise = promiseVendor_->createPromise(
      [this, b64, playbackSpeed](std::shared_ptr<Promise> promise) {
        std::thread([this, b64, playbackSpeed, promise = std::move(promise)]() {
          auto results = context_->decodeWithPCMInBase64(b64, playbackSpeed);

          if (!results) {
            promise->reject("Failed to decode audio data source.");
            return;
          }

          auto audioBufferHostObject =
              std::make_shared<AudioBufferHostObject>(results);

          promise->resolve([audioBufferHostObject = std::move(
                                audioBufferHostObject)](jsi::Runtime &runtime) {
            auto jsiObject = jsi::Object::createFromHostObject(
                runtime, audioBufferHostObject);
            jsiObject.setExternalMemoryPressure(
                runtime, audioBufferHostObject->getSizeInBytes());
            return jsiObject;
          });
        }).detach();
      });

  return promise;
}
} // namespace audioapi
