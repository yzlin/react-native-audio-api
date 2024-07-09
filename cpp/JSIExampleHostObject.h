#ifndef JSIEXAMPLEHOSTOBJECT_H
#define JSIEXAMPLEHOSTOBJECT_H

#include <jsi/jsi.h>

namespace example
{

  using namespace facebook;

  class JSI_EXPORT JSIExampleHostObject : public jsi::HostObject
  {
    public:
      explicit JSIExampleHostObject() = default;

    public:
      jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;
      void set(jsi::Runtime &, const jsi::PropNameID &name, const jsi::Value &value) override;
      std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
      static jsi::Value helloWorld(jsi::Runtime &);
  };

} // namespace margelo

#endif /* JSIEXAMPLEHOSTOBJECT_H */
