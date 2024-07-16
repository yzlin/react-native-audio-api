#include "OscillatorNode.h"
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <android/log.h>

namespace audiocontext {

    using namespace facebook::jni;

    OscillatorNode::OscillatorNode(jni::alias_ref<OscillatorNode::jhybridobject> &jThis, jlong jsContext)
            : javaObject_(make_global(jThis)), jsContext(jsContext){}

    jsi::Object OscillatorNode::createOscillatorNodeHostObject() {
        auto runtime = reinterpret_cast<jsi::Runtime *>(jsContext);
        auto hostObject = std::make_shared<OscillatorNodeHostObject>(this);
        return jsi::Object::createFromHostObject(*runtime, hostObject);
    }

    void OscillatorNode::start() {
        static const auto method = javaClassStatic()->getMethod<void()>("start");
        method(javaObject_.get());
    }

    void OscillatorNode::stop() {
        static const auto method = javaClassStatic()->getMethod<void()>("stop");
        method(javaObject_.get());
    }

    void OscillatorNode::setFrequency(jdouble frequency) {
        static const auto method = javaClassStatic()->getMethod<void(jdouble)>("setFrequency");
        method(javaObject_.get(), frequency);
    }

    void OscillatorNode::setDetune(jdouble detune) {
        static const auto method = javaClassStatic()->getMethod<void(jdouble)>("setDetune");
        method(javaObject_.get(), detune);
    }

    jni::local_ref<JString> OscillatorNode::getWaveType() {
        static const auto method = javaClassStatic()->getMethod<jni::local_ref<JString>()>("getWaveType");
        return method(javaObject_.get());
    }

    jdouble OscillatorNode::getFrequency() {
        static const auto method = javaClassLocal()->getMethod<jdouble()>("getFrequency");
        return method(javaObject_.get());
    }

    jdouble OscillatorNode::getDetune() {
        static const auto method = javaClassStatic()->getMethod<jdouble()>("getDetune");
        return method(javaObject_.get());
    }
} // namespace audiocontext
