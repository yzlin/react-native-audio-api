package com.audiocontext.context

import android.media.AudioTrack
import com.audiocontext.nodes.AudioDestinationNode
import com.audiocontext.nodes.AudioNode
import com.audiocontext.nodes.oscillator.OscillatorNode
import com.facebook.jni.HybridData
import com.facebook.react.bridge.ReactApplicationContext
import java.util.concurrent.CopyOnWriteArrayList

class AudioContext(private val reactContext: ReactApplicationContext) : BaseAudioContext {
  override var sampleRate: Int = 44100
  override val destination: AudioDestinationNode = AudioDestinationNode(this)
  override val sources = CopyOnWriteArrayList<AudioNode>()

  private val mHybridData: HybridData?;

  companion object {
    init {
      System.loadLibrary("react-native-audio-context")
    }
  }

  init {
    mHybridData = initHybrid(reactContext.javaScriptContextHolder!!.get())
  }

  external fun initHybrid(l: Long): HybridData?

  private fun addNode(node: AudioNode) {
    sources.add(node)
  }

  fun createOscillator(): OscillatorNode {
    val oscillator = OscillatorNode(this, reactContext)
    oscillator.connect(destination)
    addNode(oscillator)
    return oscillator
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
