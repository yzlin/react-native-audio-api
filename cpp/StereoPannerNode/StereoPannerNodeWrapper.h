#pragma once

#include <memory>
#include "AudioNodeWrapper.h"
#include "AudioParamWrapper.h"

#ifdef ANDROID
#include "StereoPannerNode.h"
#endif

namespace audiocontext {
    using namespace facebook;

#ifdef ANDROID
    class StereoPannerNode;
#endif

    class StereoPannerNodeWrapper: public AudioNodeWrapper {
#ifdef ANDROID
    private:
        std::shared_ptr<StereoPannerNode> panner_;
    public:
        explicit StereoPannerNodeWrapper(const std::shared_ptr<StereoPannerNode> &panner) : AudioNodeWrapper(
                panner), panner_(panner) {}
#else
        public:
        explicit PannerNodeWrapper() {}
#endif
        std::shared_ptr<AudioParamWrapper> getPanParam();
    };
} // namespace audiocontext
