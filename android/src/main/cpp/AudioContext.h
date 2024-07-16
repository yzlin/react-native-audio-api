#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <react/jni/CxxModuleWrapper.h>
#include <react/jni/JMessageQueueThread.h>
#include "AudioContextHostObject.h"
#include "OscillatorNode.h"
#include "AudioDestinationNode.h"

namespace audiocontext {

    using namespace facebook;
    using namespace facebook::jni;

    class AudioContext : public jni::HybridClass<AudioContext> {
    public:
        static auto constexpr kJavaDescriptor = "Lcom/audiocontext/context/AudioContext;";

        static jni::local_ref<AudioContext::jhybriddata> initHybrid(jni::alias_ref<jhybridobject> jThis, jlong jsContext)
        {
            return makeCxxInstance(jThis, jsContext);
        }

        static void registerNatives() {
            registerHybrid({
               makeNativeMethod("initHybrid", AudioContext::initHybrid),
           });
        }

        jsi::Object createOscillator();
        jsi::Object getDestination();

    private:
        friend HybridBase;

        global_ref<AudioContext::javaobject> javaObject_;
        jlong jsContext_;

        explicit AudioContext(jni::alias_ref<AudioContext::jhybridobject>& jThis, jlong jsContext);
    };

} // namespace audiocontext
