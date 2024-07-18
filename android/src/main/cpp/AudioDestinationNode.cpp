#include "AudioDestinationNode.h"

namespace audiocontext {

    using namespace facebook::jni;

    AudioDestinationNode::AudioDestinationNode(jni::alias_ref<AudioDestinationNode::jhybridobject> &jThis,
                               jlong jsContext): javaObject_(make_global(jThis)), jsContext_(jsContext) {}

    jsi::Object AudioDestinationNode::createAudioDestinationHostObject() {
        auto audioDestinationNodeWrapper = std::make_shared<AudioDestinationNodeWrapper>(std::shared_ptr<AudioDestinationNode>(this));
        auto runtime = reinterpret_cast<jsi::Runtime *>(jsContext_);
        auto hostObject = std::make_shared<AudioDestinationNodeHostObject>(audioDestinationNodeWrapper);
        return jsi::Object::createFromHostObject(*runtime, hostObject);
    }
} // namespace audiocontext
