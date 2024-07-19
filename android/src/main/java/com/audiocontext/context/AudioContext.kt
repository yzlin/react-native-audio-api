package com.audiocontext.context

import com.audiocontext.nodes.AudioDestinationNode
import com.audiocontext.nodes.oscillator.OscillatorNode
import com.facebook.jni.HybridData
import com.facebook.react.bridge.ReactApplicationContext

class AudioContext(reactContext: ReactApplicationContext) : BaseAudioContext {
  override val sampleRate: Int = 44100
  override val destination: AudioDestinationNode = AudioDestinationNode(this)
    get() = field

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

  external fun install()

  override fun createOscillator(): OscillatorNode {
    return OscillatorNode(this)
  }
}
