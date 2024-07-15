#include "OscillatorNode.h"
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

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
        static const auto method = javaClassLocal()->getMethod<void()>("start");
        method(javaObject_.get());
    }

    void OscillatorNode::stop() {
        static const auto method = javaClassLocal()->getMethod<void()>("stop");
        method(javaObject_.get());
    }
} // namespace audiocontext
