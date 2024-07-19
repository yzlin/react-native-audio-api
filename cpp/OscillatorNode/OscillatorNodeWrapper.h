#pragma once

#include <memory>
#include "AudioDestinationNodeWrapper.h"

#ifdef ANDROID
#include "OscillatorNode.h"
#endif

namespace audiocontext {
    using namespace facebook;

    class AudioDestinationNodeWrapper;

#ifdef ANDROID
    class OscillatorNode;
#endif

    class OscillatorNodeWrapper {
#ifdef ANDROID
    private:
        std::shared_ptr<OscillatorNode> oscillator_;
#endif

    public:
#ifdef ANDROID
        explicit OscillatorNodeWrapper(std::shared_ptr<OscillatorNode> oscillator) : oscillator_(oscillator) {}
#else
        explicit OscillatorNodeWrapper() {}
#endif
        double getFrequency();
        double getDetune();
        std::string getType();
        void start(double time);
        void stop(double time);
        void connect(std::shared_ptr<AudioDestinationNodeWrapper> destination);

        void setFrequency(double frequency);
        void setDetune(double detune);
        void setType(std::string type);

    };
} // namespace audiocontext
