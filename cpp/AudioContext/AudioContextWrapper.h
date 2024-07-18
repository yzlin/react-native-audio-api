#pragma once

#include <jsi/jsi.h>
#include "AudioContext.h"

namespace audiocontext {
    using namespace facebook;

    class AudioContext;

    class AudioContextWrapper {
    private:
        std::shared_ptr<AudioContext> audiocontext_;

    public:
        explicit AudioContextWrapper(
                std::shared_ptr<AudioContext> audiocontext) : audiocontext_(audiocontext) {}

        jsi::Value createOscillator(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
        jsi::Value getDestination(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
    };
} // namespace audiocontext
