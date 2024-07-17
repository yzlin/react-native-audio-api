#pragma once

#include <jsi/jsi.h>
#include "AudioContextWrapper.h"

namespace audiocontext {
    using namespace facebook;

    class AudioContext;

    class AudioContextHostObject : public jsi::HostObject {
    private:
        AudioContextWrapper* audiocontext_;

    public:
        explicit AudioContextHostObject(AudioContextWrapper* audiocontext) : audiocontext_(audiocontext) {}

        jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
        void set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value) override;
        std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
    };
} // namespace audiocontext
