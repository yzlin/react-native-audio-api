#include "GainNodeHostObject.h"

namespace audiocontext
{
    using namespace facebook;

    std::vector<jsi::PropNameID> GainNodeHostObject::getPropertyNames(jsi::Runtime &runtime)
    {
        std::vector<jsi::PropNameID> propertyNames;
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "gain"));
        propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "connect"));
        return propertyNames;
    }

    jsi::Value GainNodeHostObject::get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId)
    {
        auto propName = propNameId.utf8(runtime);

        if (propName == "gain")
        {
            auto gain = wrapper_->getGain();
            return jsi::Value(gain);
        }

        if (propName == "connect")
        {
            return jsi::Function::createFromHostFunction(runtime, propNameId, 1, [this](jsi::Runtime &rt, const jsi::Value &thisValue, const jsi::Value *args, size_t count) -> jsi::Value
            {
                auto node = args[0].getObject(rt).getHostObject<AudioNodeHostObject>(rt);
                wrapper_->connect(std::shared_ptr<AudioNodeHostObject>(node)->wrapper_);
                return jsi::Value::undefined();
            });
        }

        throw std::runtime_error("Prop not yet implemented!");
    }

    void GainNodeHostObject::set(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value)
    {
        auto propName = propNameId.utf8(runtime);

        if (propName == "gain")
        {
            double gain = value.getNumber();
            wrapper_->setGain(gain);
            return;
        }

        throw std::runtime_error("Not yet implemented!");
    }
}
