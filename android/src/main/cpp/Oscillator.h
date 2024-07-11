#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <react/jni/CxxModuleWrapper.h>
#include <react/jni/JMessageQueueThread.h>
#include "OscillatorHostObject.h"

namespace audiocontext {

    using namespace facebook;
    using namespace facebook::jni;

    class Oscillator : public jni::HybridClass<Oscillator> {
    public:
        static auto constexpr kJavaDescriptor = "Lcom/audiocontext/Oscillator;";

        static jni::local_ref<jhybriddata> initHybrid(jni::alias_ref<jhybridobject> jThis, jlong jsContext)
        {
          return makeCxxInstance(jThis, jsContext);
        }

        static void registerNatives() {
            javaClassStatic()->registerNatives({
                   makeNativeMethod("initHybrid", Oscillator::initHybrid),
           });
        }

        void start();
        void stop();

    private:
        friend HybridBase;

        global_ref<Oscillator::javaobject> javaObject_;

        explicit Oscillator(const jni::alias_ref<Oscillator::jhybridobject>& jThis, jlong jsContext);
    };

} // namespace audiocontext
