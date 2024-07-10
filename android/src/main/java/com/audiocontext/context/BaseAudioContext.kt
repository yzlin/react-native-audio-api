package com.audiocontext.context

import android.media.AudioTrack
import android.provider.MediaStore.Audio
import com.audiocontext.nodes.AudioDestinationNode
import com.audiocontext.nodes.AudioNode
import com.audiocontext.nodes.gain.GainNode
import com.audiocontext.nodes.oscillator.OscillatorNode
import java.util.concurrent.CopyOnWriteArrayList

interface BaseAudioContext {
  val sampleRate: Int
  val destination: AudioDestinationNode
  val sources: List<AudioNode>

  fun createOscillatorNode(): OscillatorNode
  fun createGainNode(): GainNode
  fun dispatchAudio(buffer: ShortArray, audioTrack: AudioTrack)
  fun addNode(node: AudioNode)
  fun removeNode(node: AudioNode)
}
