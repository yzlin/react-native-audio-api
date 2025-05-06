#include <audioapi/core/BaseAudioContext.h>
#include <audioapi/core/effects/GainNode.h>
#include <audioapi/utils/AudioArray.h>
#include <audioapi/utils/AudioBus.h>

namespace audioapi {

GainNode::GainNode(BaseAudioContext *context) : AudioNode(context) {
  gainParam_ = std::make_shared<AudioParam>(
      1.0, MOST_NEGATIVE_SINGLE_FLOAT, MOST_POSITIVE_SINGLE_FLOAT, context);
  isInitialized_ = true;
}

std::shared_ptr<AudioParam> GainNode::getGainParam() const {
  return gainParam_;
}

void GainNode::processNode(
    const std::shared_ptr<AudioBus> &processingBus,
    int framesToProcess) {
  double time = context_->getCurrentTime();
  auto gainParamValues = gainParam_->processParam(
      framesToProcess, time, context_->getSampleRate());
  for (int i = 0; i < framesToProcess; i += 1) {
    for (int j = 0; j < processingBus->getNumberOfChannels(); j += 1) {
      (*processingBus->getChannel(j))[i] *= gainParamValues->getData()[i];
    }
  }
}

} // namespace audioapi
