#pragma once

#include <jsi/jsi.h>
#include <fbjni/fbjni.h>
#include <fbjni/detail/Hybrid.h>
#include "AudioDestinationNode.h"

namespace audiocontext {
    using namespace facebook;

    class AudioDestinationNode;

    class AudioDestinationNodeHostObject : public jsi::HostObject {

    private:
        AudioDestinationNode* destination_;

    public:
        explicit AudioDestinationNodeHostObject(AudioDestinationNode* destination) : destination_(destination) {}

        jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
        void set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value) override;
        std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
    };
} // namespace audiocontext
