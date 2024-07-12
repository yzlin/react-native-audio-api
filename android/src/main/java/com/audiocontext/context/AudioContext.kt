package com.audiocontext.context

import android.media.AudioTrack
import com.audiocontext.nodes.AudioDestinationNode
import com.audiocontext.nodes.AudioNode
import com.audiocontext.nodes.oscillator.OscillatorNode
import com.facebook.react.bridge.ReactApplicationContext
import java.util.concurrent.CopyOnWriteArrayList

class AudioContext(private val reactContext: ReactApplicationContext) : BaseAudioContext {
  override var sampleRate: Int = 44100
  override val destination: AudioDestinationNode = AudioDestinationNode(this)
  override val sources = CopyOnWriteArrayList<AudioNode>()

  private fun addNode(node: AudioNode) {
    sources.add(node)
  }

  override fun createOscillator(): OscillatorNode {
    val oscillatorNode = OscillatorNode(this, reactContext)
    addNode(oscillatorNode)
    return oscillatorNode
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
