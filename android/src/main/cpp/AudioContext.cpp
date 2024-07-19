#include "AudioContext.h"
#include "android/log.h"

namespace audiocontext
{

  using namespace facebook::jni;

    AudioContext::AudioContext(jni::alias_ref<AudioContext::jhybridobject> &jThis,
                             jlong jsContext) : javaObject_(make_global(jThis)), jsContext_(jsContext) {}

    void AudioContext::install()
    {
        auto audioContextWrapper = std::make_shared<AudioContextWrapper>(std::shared_ptr<AudioContext>(this));
        auto runtime = reinterpret_cast<jsi::Runtime *>(jsContext_);
        auto hostObject = AudioContextHostObject::createFromWrapper(audioContextWrapper);

        auto object = jsi::Object::createFromHostObject(*runtime, hostObject);
        runtime->global().setProperty(*runtime, "__AudioContextProxy", std::move(object));
    }

  std::shared_ptr<OscillatorNode> AudioContext::createOscillator()
  {
    static const auto method = javaClassLocal()->getMethod<OscillatorNode()>("createOscillator");
    auto oscillator = method(javaObject_.get());
    auto oscillatorCppInstance = oscillator->cthis();

    return std::shared_ptr<OscillatorNode>(oscillatorCppInstance);
  }

    std::shared_ptr<AudioDestinationNode> AudioContext::getDestination()
  {
    static const auto method = javaClassLocal()->getMethod<AudioDestinationNode()>("getDestination");
    auto destination = method(javaObject_.get());
    auto destinationCppInstance = destination->cthis();

    return std::shared_ptr<AudioDestinationNode>(destinationCppInstance);
  }

} // namespace audiocontext
