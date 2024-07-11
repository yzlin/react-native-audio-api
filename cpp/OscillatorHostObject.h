#pragma once

#include <jsi/jsi.h>
#include <fbjni/fbjni.h>
#include <fbjni/detail/Hybrid.h>
#include "Oscillator.h"

namespace audiocontext {
    using namespace facebook;

    class Oscillator;

    class OscillatorHostObject : public jsi::HostObject {
    private:
        Oscillator* oscillator_;

    public:
        explicit OscillatorHostObject(Oscillator* oscillator) : oscillator_(oscillator) {}

        jsi::Value get(jsi::Runtime& runtime, const jsi::PropNameID& name) override;
        void set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value) override;
        std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override;
    };
} // namespace audiocontext
