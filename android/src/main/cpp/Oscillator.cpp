#include "Oscillator.h"
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

namespace audiocontext {

    using namespace facebook::jni;

    Oscillator::Oscillator(const jni::alias_ref<Oscillator::jhybridobject> &jThis,
                                    jlong jsContext): javaObject_(make_global(jThis)) {
        auto runtime = reinterpret_cast<jsi::Runtime *>(jsContext);
        auto hostObject = std::make_shared<OscillatorHostObject>(this);
        auto object = jsi::Object::createFromHostObject(*runtime, hostObject);
        runtime->global().setProperty(*runtime, "__OscillatorProxy", std::move(object));
    }

    void Oscillator::start() {
        static const auto method = javaClassStatic()->getMethod<void()>("start");
        method(javaObject_.get());
    }

    void Oscillator::stop() {
        static const auto method = javaClassStatic()->getMethod<void()>("stop");
        method(javaObject_.get());
    }

} // namespace audiocontext
