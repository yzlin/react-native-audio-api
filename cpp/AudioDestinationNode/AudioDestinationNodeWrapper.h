#pragma once

#include <jsi/jsi.h>
#include "AudioDestinationNode.h"
#include "OscillatorNodeWrapper.h"

namespace audiocontext {
    using namespace facebook;

    class AudioDestinationNode;

    class AudioDestinationNodeWrapper {
    private:
        friend class OscillatorNodeWrapper;

        std::shared_ptr<AudioDestinationNode> destination_;

    public:
        explicit AudioDestinationNodeWrapper(std::shared_ptr<AudioDestinationNode> destination) : destination_(destination) {}
    };
} // namespace audiocontext
