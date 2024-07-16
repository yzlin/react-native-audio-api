#include "OscillatorNodeHostObject.h"
#include <android/log.h>

namespace audiocontext {
    using namespace facebook;

    std::vector<jsi::PropNameID> OscillatorNodeHostObject::getPropertyNames(jsi::Runtime& runtime) {
        std::vector<jsi::PropNameID> propertyNames;
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "start"));
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "stop"));
        return propertyNames;
    }

    jsi::Value OscillatorNodeHostObject::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
        auto propName = propNameId.utf8(runtime);

        if (propName == "start") {
            return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                oscillator_->start();
                return jsi::Value::undefined();
            });
        }

        if (propName == "stop") {
            return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                oscillator_->stop();
                return jsi::Value::undefined();
            });
        }

        if (propName == "wave") {
            return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                auto waveTypeJString = oscillator_->getWaveType();
                std::string waveTypeStr = waveTypeJString->toStdString();
                return jsi::String::createFromUtf8(rt, waveTypeStr);
            });
        }

        if (propName == "frequency") {
            return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                auto frequency = oscillator_->getFrequency();
                return {frequency};
            });
        }

        if (propName == "detune") {
            return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
                auto detune = oscillator_->getDetune();
                return {detune};
            });
        }

        throw std::runtime_error("Prop not yet implemented!");
    }

    void OscillatorNodeHostObject::set(jsi::Runtime& runtime, const jsi::PropNameID& propNameId, const jsi::Value& value) {
        auto propName = propNameId.utf8(runtime);

        if (propName == "frequency") {
            auto frequency = value.asNumber();
            oscillator_->setFrequency(frequency);
            return;
        }

        if (propName == "detune") {
            auto detune = value.asNumber();
            oscillator_->setDetune(detune);
            return;
        }

        throw std::runtime_error("Not yet implemented!");
    }
}
