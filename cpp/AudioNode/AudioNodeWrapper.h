#pragma once

#include <memory>

#ifdef ANDROID
#include "AudioNode.h"
#endif

namespace audiocontext {
    class AudioNodeWrapper {
#ifdef ANDROID
    protected:
        std::shared_ptr<AudioNode> node_;
    public:
        explicit AudioNodeWrapper(const std::shared_ptr<AudioNode> &node);
#else
    public:
        explicit AudioNodeWrapper() {}
#endif
    private:
        int numberOfInputs_;
        int numberOfOutputs_;
    public:
        int getNumberOfInputs() const;
        int getNumberOfOutputs() const;
        void connect(const std::shared_ptr<AudioNodeWrapper> &node) const;
        void disconnect(const std::shared_ptr<AudioNodeWrapper> &node) const;
    };
} // namespace audiocontext
