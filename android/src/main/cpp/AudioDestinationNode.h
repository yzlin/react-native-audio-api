#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <react/jni/CxxModuleWrapper.h>
#include <react/jni/JMessageQueueThread.h>
#include "AudioDestinationNodeHostObject.h"
#include "OscillatorNode.h"

namespace audiocontext {

    using namespace facebook;
    using namespace facebook::jni;

    class OscillatorNode;

    class AudioDestinationNode : public jni::HybridClass<AudioDestinationNode> {
    public:
        static auto constexpr kJavaDescriptor = "Lcom/audiocontext/nodes/AudioDestinationNode;";

        static jni::local_ref<AudioDestinationNode::jhybriddata> initHybrid(jni::alias_ref<jhybridobject> jThis, jlong jsContext)
        {
            return makeCxxInstance(jThis, jsContext);
        }

        static void registerNatives() {
            registerHybrid({
               makeNativeMethod("initHybrid", AudioDestinationNode::initHybrid),
           });
        }

        jsi::Object createAudioDestinationHostObject();

    private:
        friend HybridBase;
        friend class OscillatorNode;

        global_ref<AudioDestinationNode::javaobject> javaObject_;
        jlong jsContext_{};

        explicit AudioDestinationNode(jni::alias_ref<AudioDestinationNode::jhybridobject>& jThis, jlong jsContext);
    };

} // namespace audiocontext
