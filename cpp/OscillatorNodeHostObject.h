#pragma once

#include <jsi/jsi.h>
#include <fbjni/fbjni.h>
#include <fbjni/detail/Hybrid.h>
#include "OscillatorNode.h"

namespace audiocontext {
    using namespace facebook;

    class OscillatorNode;

    class OscillatorNodeHostObject : public jsi::HostObject {
    private:
        OscillatorNode* oscillator_;

    public:
        explicit OscillatorNodeHostObject(OscillatorNode* oscillator) : oscillator_(oscillator) {}

        jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
        void set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value) override;
        std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;

        jsi::Value start(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
        jsi::Value stop(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
        jsi::Value frequency(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
        jsi::Value detune(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
        jsi::Value connect(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
    };
} // namespace audiocontext
