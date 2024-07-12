package com.audiocontext.context

import android.media.AudioTrack
import com.audiocontext.nodes.AudioDestinationNode
import com.audiocontext.nodes.AudioNode
import com.audiocontext.nodes.oscillator.OscillatorNode

interface BaseAudioContext {
  val sampleRate: Int
  val destination: AudioDestinationNode
  val sources: List<AudioNode>

  fun createOscillator(): OscillatorNode
  abstract fun dispatchAudio(buffer: ShortArray, audioTrack: AudioTrack)
}
