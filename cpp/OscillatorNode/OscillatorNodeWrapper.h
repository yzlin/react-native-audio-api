#pragma once

#include <jsi/jsi.h>
#include "OscillatorNode.h"

namespace audiocontext {
    using namespace facebook;

    class OscillatorNode;

    class OscillatorNodeWrapper {
    private:
        std::shared_ptr<OscillatorNode> oscillator_;

    public:
        explicit OscillatorNodeWrapper(std::shared_ptr<OscillatorNode> oscillator) : oscillator_(oscillator) {}

        jsi::Value getFrequency(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);
        jsi::Value getDetune(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);
        jsi::Value getType(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);
        jsi::Value start(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);
        jsi::Value stop(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);
        jsi::Value connect(jsi::Runtime &runtime, const jsi::PropNameID &propNameId);

        void setFrequency(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value);
        void setDetune(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value);
        void setType(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value);

    };
} // namespace audiocontext
