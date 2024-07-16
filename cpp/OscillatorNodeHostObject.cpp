#include "OscillatorNodeHostObject.h"
#include <android/log.h>

namespace audiocontext {
    using namespace facebook;

    std::vector<jsi::PropNameID> OscillatorNodeHostObject::getPropertyNames(jsi::Runtime& runtime) {
        std::vector<jsi::PropNameID> propertyNames;
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "start"));
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "stop"));
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "frequency"));
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "detune"));
        return propertyNames;
    }

    jsi::Value OscillatorNodeHostObject::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
        auto propName = propNameId.utf8(runtime);

        if (propName == "start") {
            return start(runtime, propNameId);
        }

        if (propName == "stop") {
            return stop(runtime, propNameId);
        }

        if (propName == "frequency") {
            return frequency(runtime, propNameId);
        }

        if (propName == "detune") {
            return detune(runtime, propNameId);
        }

        if (propName == "connect") {
            return connect(runtime, propNameId);
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

    jsi::Value OscillatorNodeHostObject::start(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
            oscillator_->start();
            return jsi::Value::undefined();
        });
    }

    jsi::Value OscillatorNodeHostObject::stop(jsi::Runtime &runtime,
                                              const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
            oscillator_->stop();
            return jsi::Value::undefined();
        });
    }

    jsi::Value OscillatorNodeHostObject::frequency(jsi::Runtime &runtime,
                                                   const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
            auto frequency = oscillator_->getFrequency();
            return jsi::Value(frequency);
        });
    }

    jsi::Value OscillatorNodeHostObject::detune(jsi::Runtime &runtime,
                                                const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
            auto detune = oscillator_->getDetune();
            return jsi::Value(detune);
        });
    }

    jsi::Value OscillatorNodeHostObject::connect(jsi::Runtime &runtime,
                                                 const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 1, [this](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
            auto destination = args[0].asObject(rt).asHostObject<AudioDestinationNodeHostObject>(rt);
            oscillator_->connect(*destination->destination_);
            return jsi::Value::undefined();
        });
    }
}
