#pragma once

#include <memory>

#ifdef ANDROID
#include "AudioParam.h"
#endif

namespace audiocontext {
    using namespace facebook;

    class AudioParamWrapper {
#ifdef ANDROID
    protected:
        std::shared_ptr<AudioParam> param_;
        double defaultValue_;
        double minValue_;
        double maxValue_;
    public:
        explicit AudioParamWrapper(const std::shared_ptr<AudioParam> &param);
#else
        public:
        explicit AudioParamWrapper() {}
#endif
    public:
        double getValue();
        void setValue(double value);
        double getDefaultValue() const;
        double getMinValue() const;
        double getMaxValue() const;
    };
} // namespace audiocontext
