#include "StereoPannerNodeWrapper.h"

namespace audiocontext {

    std::shared_ptr<AudioParamWrapper> StereoPannerNodeWrapper::getPanParam() {
        auto pan = panner_->getPanParam();
        return std::make_shared<AudioParamWrapper>(pan);
    }
} // namespace audiocontext
