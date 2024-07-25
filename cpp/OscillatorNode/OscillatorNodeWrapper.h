#pragma once

#include <memory>
#include "AudioNodeWrapper.h"
#include "AudioParamWrapper.h"

#ifdef ANDROID
#include "OscillatorNode.h"
#endif

namespace audiocontext {
    using namespace facebook;

#ifdef ANDROID
    class OscillatorNode;
#endif

    class OscillatorNodeWrapper: public AudioNodeWrapper {
#ifdef ANDROID
    private:
        std::shared_ptr<OscillatorNode> oscillator_;
    public:
        explicit OscillatorNodeWrapper(const std::shared_ptr<OscillatorNode> &oscillator) : AudioNodeWrapper(
                oscillator), oscillator_(oscillator) {}
#else
    public:
        explicit OscillatorNodeWrapper() {}
#endif
        std::shared_ptr<AudioParamWrapper> getFrequency();
        std::shared_ptr<AudioParamWrapper> getDetune();
        std::string getType();
        void start(double time);
        void stop(double time);
        void setType(const std::string& type);
    };
} // namespace audiocontext
