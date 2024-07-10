package com.audiocontext.nativemodules

import com.audiocontext.context.AudioContext
import com.audiocontext.nodes.AudioNode
import com.audiocontext.nodes.AudioScheduledSourceNode
import com.audiocontext.nodes.gain.GainNode
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod

class AudioContextModule(reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext) {
  private val audioContext = AudioContext()
  private var source: AudioScheduledSourceNode? = null
  private var destination: AudioNode = audioContext.destination

  override fun getName(): String {
    return "AudioContextModule"
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  fun createOscillatorNode() {
    source = audioContext.createOscillatorNode()
  }

  @ReactMethod
  fun start() {
    source?.start()
  }

  @ReactMethod
  fun stop() {
    source?.stop()
  }

  @ReactMethod
  fun connect() {
    source?.connect(destination)
  }

  @ReactMethod
  fun disconnect() {
    source?.disconnect()
  }
}
