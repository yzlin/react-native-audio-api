#ifndef AUDIOCONTEXTHOSTOBJECT_H
#define AUDIOCONTEXTHOSTOBJECT_H

#include <jsi/jsi.h>
#include <jni.h>

namespace audiocontext
{

  using namespace facebook;

  class JSI_EXPORT AudioContextHostObject : public jsi::HostObject
  {
    private:
      jobject audioContext;

    public:
      explicit AudioContextHostObject();
      ~AudioContextHostObject();

    public:
      jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;
      void set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) override;
      std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
      jsi::Value createOscillator(jsi::Runtime &rt);
  };

} // namespace audiocontext

#endif /* AUDIOCONTEXTHOSTOBJECT_H */
