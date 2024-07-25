#include "GainNodeWrapper.h"

namespace audiocontext {

    std::shared_ptr<AudioParamWrapper> GainNodeWrapper::getGainParam() {
        auto gain = gain_->getGainParam();
        return std::make_shared<AudioParamWrapper>(gain);
    }
} // namespace audiocontext
