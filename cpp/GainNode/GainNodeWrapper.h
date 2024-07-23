#pragma once

#include <memory>
#include "AudioNodeWrapper.h"

#ifdef ANDROID
#include "GainNode.h"
#endif

namespace audiocontext {
    using namespace facebook;

#ifdef ANDROID
    class GainNode;
#endif

    class GainNodeWrapper: public AudioNodeWrapper {
#ifdef ANDROID
    private:
        std::shared_ptr<GainNode> gain_;
#endif

    public:
#ifdef ANDROID
        explicit GainNodeWrapper( std::shared_ptr<GainNode> gain) : AudioNodeWrapper(
                gain), gain_(gain) {}
#else
        explicit GainNodeWrapper() {}
#endif
        double getGain();
        void setGain(double gain);
    };
} // namespace audiocontext
