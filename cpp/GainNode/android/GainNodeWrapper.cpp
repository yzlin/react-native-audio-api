#include "GainNodeWrapper.h"

namespace audiocontext {

    std::shared_ptr<AudioParamWrapper> GainNodeWrapper::getGain() {
        auto gain = gain_->getGain();
        return std::make_shared<AudioParamWrapper>(gain);
    }
} // namespace audiocontext
