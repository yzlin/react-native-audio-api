#include "OscillatorNodeWrapper.h"

namespace audiocontext {

    std::shared_ptr<AudioParamWrapper> OscillatorNodeWrapper::getFrequencyParam() {
        auto frequency = oscillator_->getFrequencyParam();
        return std::make_shared<AudioParamWrapper>(frequency);
    }

    std::shared_ptr<AudioParamWrapper> OscillatorNodeWrapper::getDetuneParam() {
        auto detune = oscillator_->getDetuneParam();
        return std::make_shared<AudioParamWrapper>(detune);
    }

    std::string OscillatorNodeWrapper::getType() {
        return oscillator_->getWaveType();
    }

    void OscillatorNodeWrapper::start(double time) {
        oscillator_->start(time);
    }

    void OscillatorNodeWrapper::stop(double time) {
        oscillator_->stop(time);
    }

    void OscillatorNodeWrapper::setType(const std::string& type) {
        oscillator_->setWaveType(type);
    }
}
