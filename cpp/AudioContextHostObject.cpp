#include "AudioContextHostObject.h"
#include <jsi/jsi.h>
#include <jni.h>

namespace audiocontext {
  using namespace facebook;


  AudioContextHostObject::AudioContextHostObject()
  {
  }

  AudioContextHostObject::~AudioContextHostObject()
  {

  }

  std::vector<jsi::PropNameID> AudioContextHostObject::getPropertyNames(jsi::Runtime & runtime)
  {
    std::vector<jsi::PropNameID> propertyNames;
    //propertyNames.push_back(jsi::PropNameID::forAscii(runtime, "createOscillator"));
    return propertyNames;
  }

  jsi::Value AudioContextHostObject::get(jsi::Runtime & runtime, const jsi::PropNameID &propNameId)
  {
    auto propName = propNameId.utf8(runtime);

    // if (propName == "createOscillator")
    // {
    //   return jsi::Function::createFromHostFunction(runtime, propNameId, 0,
    //                                                 [this](jsi::Runtime &rt, const jsi::Value &, const jsi::Value *, size_t)
    //                                                 {
    //                                                   return this->createOscillator(rt);
    //                                                 });
    // }

    throw std::runtime_error("Not yet implemented!");
  }

  void AudioContextHostObject::set(jsi::Runtime & runtime, const jsi::PropNameID &propNameId, const jsi::Value &value)
  {
    auto propName = propNameId.utf8(runtime);

    throw std::runtime_error("Not yet implemented!");
  }

  jsi::Value AudioContextHostObject::createOscillator(jsi::Runtime & runtime)
  {
    return jsi::Value::undefined();
  }
}
