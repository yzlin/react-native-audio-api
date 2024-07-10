package com.audiocontext.context

import android.media.AudioTrack
import com.audiocontext.nodes.AudioDestinationNode
import com.audiocontext.nodes.AudioNode
import com.audiocontext.nodes.gain.GainNode
import com.audiocontext.nodes.oscillator.OscillatorNode
import java.util.concurrent.CopyOnWriteArrayList

class AudioContext : BaseAudioContext {
  override var sampleRate: Int = 44100
  override val destination: AudioDestinationNode = AudioDestinationNode(this)
  override val sources = CopyOnWriteArrayList<AudioNode>()

  override fun addNode(node: AudioNode) {
    sources.add(node)
  }

  override fun removeNode(node: AudioNode) {
    sources.remove(node)
  }

  override fun createOscillatorNode(): OscillatorNode {
    val oscillatorNode = OscillatorNode(this)
    addNode(oscillatorNode)
    return oscillatorNode
  }

  override fun createGainNode(): GainNode {
    val gainNode = GainNode(this)
    return gainNode
  }

  override fun dispatchAudio(buffer: ShortArray, audioTrack: AudioTrack) {
    val currentBuffer = buffer.clone()

    synchronized(sources) {
      sources.forEach { source ->
        source.process(currentBuffer, audioTrack)
      }
    }
  }
}
