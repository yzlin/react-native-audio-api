#pragma once

#include <memory>
#include "AudioNodeWrapper.h"

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
#endif

    public:
#ifdef ANDROID
    explicit OscillatorNodeWrapper( std::shared_ptr<OscillatorNode> oscillator) : AudioNodeWrapper(
            oscillator), oscillator_(oscillator) {}
#else
        explicit OscillatorNodeWrapper() {}
#endif
        double getFrequency();
        double getDetune();
        std::string getType();
        void start(double time);
        void stop(double time);

        void setFrequency(double frequency);
        void setDetune(double detune);
        void setType(const std::string& type);
    };
} // namespace audiocontext
