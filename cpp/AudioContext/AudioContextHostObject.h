#pragma once

#include <jsi/jsi.h>
#include "AudioContextWrapper.h"

namespace audiocontext
{
    using namespace facebook;

    class AudioContextWrapper;

    class AudioContextHostObject : public jsi::HostObject
    {
    private:
        std::shared_ptr<AudioContextWrapper> wrapper_;

    public:
        explicit AudioContextHostObject(std::shared_ptr<AudioContextWrapper> wrapper) : wrapper_(wrapper) {}

        static std::shared_ptr<AudioContextHostObject> createFromWrapper(std::shared_ptr<AudioContextWrapper> wrapper) {
            return std::make_shared<AudioContextHostObject>(wrapper);
        }

        jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;
        void set(jsi::Runtime &runtime, const jsi::PropNameID &name, const jsi::Value &value) override;
        std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

        jsi::Value createOscillator(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);
        jsi::Value getDestination(jsi::Runtime& runtime, const jsi::PropNameID& propNameId);

  };
} // namespace audiocontext
