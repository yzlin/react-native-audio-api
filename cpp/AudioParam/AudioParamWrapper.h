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
    public:
        explicit AudioParamWrapper(const std::shared_ptr<AudioParam> &param) : param_(param) {}
#else
        public:
        explicit AudioParamWrapper() {}
#endif
    public:
        double getValue();
        void setValue(double value);
    };
} // namespace audiocontext
