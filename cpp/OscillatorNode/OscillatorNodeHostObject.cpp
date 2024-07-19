#include "OscillatorNodeHostObject.h"

namespace audiocontext
{
  using namespace facebook;

  std::vector<jsi::PropNameID> OscillatorNodeHostObject::getPropertyNames(jsi::Runtime &runtime)
  {
    std::vector<jsi::PropNameID> propertyNames;
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "start"));
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "stop"));
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "frequency"));
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "detune"));
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "type"));
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "connect"));
    return propertyNames;
  }

  jsi::Value OscillatorNodeHostObject::get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId)
  {
    auto propName = propNameId.utf8(runtime);

    if (propName == "start")
    {
      return start(runtime, propNameId);
    }

    if (propName == "stop")
    {
        return stop(runtime, propNameId);
    }

    if (propName == "frequency")
    {
        return getFrequency(runtime, propNameId);
    }

    if (propName == "detune")
    {
        return getDetune(runtime, propNameId);
    }

    if (propName == "type")
    {
        return getType(runtime, propNameId);
    }

    if (propName == "connect")
    {
        return connect(runtime, propNameId);
    }

    throw std::runtime_error("Prop not yet implemented!");
  }

  void OscillatorNodeHostObject::set(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value)
  {
    auto propName = propNameId.utf8(runtime);

    if (propName == "frequency")
    {
        setFrequency(runtime, propNameId, value);
        return;
    }

    if (propName == "detune")
    {

        setDetune(runtime, propNameId, value);
        return;
    }

    if (propName == "type")
    {
        setType(runtime, propNameId, value);
        return;
    }

    throw std::runtime_error("Not yet implemented!");
  }

    jsi::Value OscillatorNodeHostObject::getFrequency(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
        {
            auto frequency = wrapper_->getFrequency();
            return jsi::Value(frequency);
        });
    }

    jsi::Value OscillatorNodeHostObject::getDetune(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
        {
            auto detune = wrapper_->getDetune();
            return jsi::Value(detune);
        });
    }

    jsi::Value OscillatorNodeHostObject::getType(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
        {
            auto waveType = wrapper_->getType();
            return jsi::String::createFromUtf8(rt, waveType);
        });
    }

    jsi::Value OscillatorNodeHostObject::start(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
        {
            auto time = args[0].getNumber();
            wrapper_->start(time);
            return jsi::Value::undefined();
        });
    }

    jsi::Value OscillatorNodeHostObject::stop(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 0, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
        {
            auto time = args[0].getNumber();
            wrapper_->stop(time);
            return jsi::Value::undefined();
        });
    }

    jsi::Value OscillatorNodeHostObject::connect(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
        return jsi::Function::createFromHostFunction(runtime, propNameId, 1, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
        {
            auto destination = args[0].getObject(rt).getHostObject<AudioDestinationNodeHostObject>(rt);
            wrapper_->connect(std::shared_ptr<AudioDestinationNodeWrapper>(destination->wrapper_));
            return jsi::Value::undefined();
        });
    }

    void OscillatorNodeHostObject::setFrequency(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value) {
        double frequency = value.getNumber();
        wrapper_->setFrequency(frequency);
    }

    void OscillatorNodeHostObject::setDetune(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value) {
        double detune = value.getNumber();
        wrapper_->setDetune(detune);
    }

    void OscillatorNodeHostObject::setType(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value) {
        std::string waveType = value.getString(runtime).utf8(runtime);
        wrapper_->setType(waveType);
    }
}
