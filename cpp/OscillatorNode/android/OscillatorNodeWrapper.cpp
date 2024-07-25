#include "OscillatorNodeWrapper.h"

namespace audiocontext {

    std::shared_ptr<AudioParamWrapper> OscillatorNodeWrapper::getFrequency() {
        auto frequency = oscillator_->getFrequency();
        return std::make_shared<AudioParamWrapper>(frequency);
    }

    std::shared_ptr<AudioParamWrapper> OscillatorNodeWrapper::getDetune() {
        auto detune = oscillator_->getDetune();
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
