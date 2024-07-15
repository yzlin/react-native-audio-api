package com.audiocontext.nativemodules

import com.audiocontext.context.AudioContext
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod

class AudioContextModule(private val reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext) {
  private val audioContext = AudioContext(reactContext)
  private val destination = audioContext.destination

  override fun getName(): String {
    return "AudioContextModule"
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  fun createOscillator() {
    val oscillator = audioContext.createOscillator()
    //oscillator.connect(destination)
  }
}
