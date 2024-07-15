#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <react/jni/CxxModuleWrapper.h>
#include <react/jni/JMessageQueueThread.h>
#include "AudioContextHostObject.h"
#include "OscillatorNode.h"

namespace audiocontext {

    using namespace facebook;
    using namespace facebook::jni;

    class AudioContext : public jni::HybridClass<AudioContext> {
    public:
        static auto constexpr kJavaDescriptor = "Lcom/audiocontext/nodes/context/AudioContext;";

        static jni::local_ref<AudioContext::jhybriddata> initHybrid(jni::alias_ref<jhybridobject> jThis, jlong jsContext)
        {
            return makeCxxInstance(jThis, jsContext);
        }

        static void registerNatives() {
            registerHybrid({
               makeNativeMethod("initHybrid", AudioContext::initHybrid),
           });
        }

        jni::local_ref<OscillatorNode::jhybriddata> createOscillator();
        jsi::Value jsiCreateOscillator(jsi::Runtime &runtime);

    private:
        friend HybridBase;

        global_ref<AudioContext::javaobject> javaObject_;
        std::shared_ptr<jsi::Runtime> runtime_;

        explicit AudioContext(jni::alias_ref<AudioContext::jhybridobject>& jThis, jlong jsContext);
    };

} // namespace audiocontext
