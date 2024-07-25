#pragma once

#include <memory>
#include <utility>
#include "OscillatorNodeWrapper.h"
#include "AudioDestinationNodeWrapper.h"
#include "GainNodeWrapper.h"
#include "StereoPannerNodeWrapper.h"

#ifdef ANDROID
#include "AudioContext.h"
#endif

namespace audiocontext {
    using namespace facebook;

    class OscillatorNodeWrapper;
    class AudioDestinationNodeWrapper;

#ifdef ANDROID
    class AudioContext;
#endif

    class AudioContextWrapper {
#ifdef ANDROID
    private:
        std::shared_ptr<AudioContext> audiocontext_;

    public:
        explicit AudioContextWrapper(const std::shared_ptr<AudioContext> &audiocontext);
#else
    public
        explicit AudioContextWrapper() {}
#endif
    private:
        std::shared_ptr<AudioDestinationNodeWrapper> destinationNode_;
    public:
        std::shared_ptr<OscillatorNodeWrapper> createOscillator();
        std::shared_ptr<AudioDestinationNodeWrapper> getDestination();
        std::shared_ptr<GainNodeWrapper> createGain();
        std::shared_ptr<StereoPannerNodeWrapper> createStereoPanner();
    };
} // namespace audiocontext
