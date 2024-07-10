#ifndef OSCILLATORNODEHOSTOBJECT_H
#define OSCILLATORNODEHOSTOBJECT_H

#include <jsi/jsi.h>
#include <jni.h>
#include "AudioContextHostObject.h"

namespace oscillatornode
{

  using namespace facebook;

  class JSI_EXPORT OscillatorNodeHostObject : public jsi::HostObject
  {
  public:
    explicit OscillatorNodeHostObject(AudioContextHostObject context);

  public:
    jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;
    void set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) override;
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
  };

} // namespace oscillatornode

#endif /* OSCILLATORNODEHOSTOBJECT_H */
