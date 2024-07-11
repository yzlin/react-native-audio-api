package com.audiocontext.nodes.gain

import android.media.AudioTrack
import com.audiocontext.context.BaseAudioContext
import com.audiocontext.nodes.AudioNode

class GainNode(context: BaseAudioContext): AudioNode(context) {
  override val numberOfInputs = 1
  override val numberOfOutputs = 1
  var gain: Double = 1.0
    get() = field
    set(value) {
      field = value
      if (field < 0) field = 0.0
      if (field > 1) field = 1.0
    }

  override fun process(buffer: ShortArray, audioTrack: AudioTrack) {
    audioTrack.setVolume(gain.toFloat())
    super.process(buffer, audioTrack)
  }
}
