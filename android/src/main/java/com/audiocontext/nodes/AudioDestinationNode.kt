package com.audiocontext.nodes

import android.media.AudioTrack
import com.audiocontext.context.BaseAudioContext


class AudioDestinationNode(context: BaseAudioContext): AudioNode(context) {
  override val numberOfInputs = 1
  override val numberOfOutputs = 0

  override fun process(buffer: ShortArray, audioTrack: AudioTrack) {
    audioTrack.write(buffer, 0, buffer.size)
  }
}
