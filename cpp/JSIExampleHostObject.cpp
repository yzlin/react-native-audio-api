#include "JSIExampleHostObject.h"
#include <jsi/jsi.h>

namespace example {
  using namespace facebook;

  std::vector<jsi::PropNameID> JSIExampleHostObject::getPropertyNames(jsi::Runtime &runtime)
  {
    std::vector<jsi::PropNameID> propertyNames;
    propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "helloWorld"));
    return propertyNames;
  }

  jsi::Value JSIExampleHostObject::get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId)
  {
    auto propName = propNameId.utf8(runtime);

    if (propName == "helloWorld")
    {
      return jsi::Function::createFromHostFunction(runtime, propNameId, 0,
        [this](jsi::Runtime &rt, const jsi::Value &, const jsi::Value *, size_t)
          {
            return this->helloWorld(rt);
          });
    }

    throw std::runtime_error("Not yet implemented!");
  }

  void JSIExampleHostObject::set(jsi::Runtime &runtime, const jsi::PropNameID &propNameId, const jsi::Value &value)
  {
    auto propName = propNameId.utf8(runtime);
    if (propName == "helloWorld")
    {
      // Do nothing
      return;
    }
    throw std::runtime_error("Not yet implemented!");
  }

  jsi::Value JSIExampleHostObject::helloWorld(jsi::Runtime &runtime)
  {
    return jsi::String::createFromUtf8(runtime, "Hello World using jsi::HostObject!");
  }
}
