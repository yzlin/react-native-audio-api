#include "StereoPannerNodeWrapper.h"

namespace audiocontext {

    std::shared_ptr<AudioParamWrapper> StereoPannerNodeWrapper::getPan() {
        auto pan = panner_->getPan();
        return std::make_shared<AudioParamWrapper>(pan);
    }
} // namespace audiocontext
