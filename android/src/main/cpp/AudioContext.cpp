#include "AudioContext.h"
#include "AudioContextHostObject.h"
#include "OscillatorNode.h"
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <android/log.h>

namespace audiocontext {

    using namespace facebook::jni;

    AudioContext::AudioContext(jni::alias_ref<AudioContext::jhybridobject> &jThis,
                                   jlong jsContext): javaObject_(make_global(jThis)) {
        auto runtime = reinterpret_cast<jsi::Runtime *>(jsContext);
        auto hostObject = std::make_shared<AudioContextHostObject>(this);
        auto object = jsi::Object::createFromHostObject(*runtime, hostObject);
        runtime->global().setProperty(*runtime, "__AudioContextProxy", std::move(object));
    }

    jsi::Object AudioContext::createOscillator() {
        static const auto method = javaClassLocal()->getMethod<OscillatorNode()>("createOscillator");
        auto oscillator = method(javaObject_.get());
        auto oscillatorCppInstance = oscillator->cthis();

        return oscillatorCppInstance->createOscillatorNodeHostObject();
    }

} // namespace audiocontext
