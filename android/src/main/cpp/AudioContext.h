#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

namespace audiocontext {
    using namespace facebook;
    using namespace facebook::jni;

    class AudioContext: public HybridClass<AudioContext> {
        public:
            static auto constexpr kJavaDescriptor =
                "Lcom/audiocontext/context/AudioContext;";

            static void registerNatives() {
                javaClassStatic()->registerNatives({
                    makeNativeMethod("initHybrid", AudioContext::initHybrid),
                });
            }

            static HybridBase* initHybrid(alias_ref<jhybridobject> jThis) {
                return new AudioContext(jThis);
            }

    private:
            global_ref<jobject> javaObject_;
    };
}
