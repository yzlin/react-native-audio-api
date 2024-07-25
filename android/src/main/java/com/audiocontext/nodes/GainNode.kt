package com.audiocontext.nodes

import android.media.AudioTrack
import com.audiocontext.context.BaseAudioContext
import com.facebook.jni.HybridData

class GainNode(context: BaseAudioContext): AudioNode(context) {
  override val numberOfInputs: Int = 1
  override val numberOfOutputs: Int = 1
  private var gain: Double = 1.0
    get() = field
    set(value) {
      field = value
    }

  private val mHybridData: HybridData? = initHybrid();

  override fun process(buffer: ShortArray, audioTrack: AudioTrack) {
    audioTrack.setVolume(gain.toFloat())
    super.process(buffer, audioTrack)
  }
}
