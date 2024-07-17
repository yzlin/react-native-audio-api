#include "AudioContextWrapper.h"

namespace audiocontext {

    jsi::Value AudioContextWrapper::createOscillator(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
            return audiocontext_->createOscillator();
        });
    }

    jsi::Value AudioContextWrapper::getDestination(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
            return audiocontext_->getDestination();
        });
    }
} // namespace audiocontext
