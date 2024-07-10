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

  jsi::Value JSIExampleHostObject::get(jsi::Runtime &runtime, const jsi::PropNameID &propNameId) {
    auto propName = propNameId.utf8(runtime);

    if (propName == "helloWorld") {
      return jsi::Function::createFromHostFunction(runtime, propNameId, 2,
        [this](jsi::Runtime &rt, const jsi::Value &, const jsi::Value *args, size_t count) {
          if (count != 2) {
            throw std::invalid_argument("helloWorld expects exactly two arguments");
          }
          return this->helloWorld(rt, args[0], args[1]);
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

  jsi::Value JSIExampleHostObject::helloWorld(jsi::Runtime &runtime, const jsi::Value &value, const jsi::Value &value2) {
    if (value.isNumber() && value2.isNumber()) {
      // Extract numbers and add them
      double result = value.asNumber() + value2.asNumber();
      return jsi::Value(result);
    } else {
      // Handle other cases (e.g., one is a number and the other is a string)
      return jsi::Value::undefined();
    }
  }
}
