package com.audiocontext.nodes.oscillator

import android.media.AudioFormat
import android.media.AudioManager
import android.media.AudioTrack
import com.audiocontext.context.BaseAudioContext
import com.audiocontext.nodes.AudioScheduledSourceNode
import com.facebook.jni.HybridData
import com.facebook.react.bridge.ReactApplicationContext
import kotlin.math.abs
import kotlin.math.floor
import kotlin.math.sin

class OscillatorNode(context: BaseAudioContext, reactContext: ReactApplicationContext) : AudioScheduledSourceNode(context) {
  override val numberOfInputs: Int = 0
  override val numberOfOutputs: Int = 1
  private var frequency: Double = 440.0
  private var detune: Double = 0.0
  private var waveType: WaveType = WaveType.SINE

  private val audioTrack: AudioTrack
  @Volatile private var isPlaying: Boolean = false
  private var playbackThread: Thread? = null
  private var buffer: ShortArray = ShortArray(1024)

  private val mHybridData: HybridData?;

  companion object {
    init {
      System.loadLibrary("react-native-audio-context")
    }
  }

  init {
    mHybridData = initHybrid(reactContext.javaScriptContextHolder!!.get())

    val bufferSize = AudioTrack.getMinBufferSize(
      context.sampleRate,
      AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT)
    this.audioTrack = AudioTrack(
      AudioManager.STREAM_MUSIC, context.sampleRate, AudioFormat.CHANNEL_OUT_MONO,
      AudioFormat.ENCODING_PCM_16BIT, bufferSize, AudioTrack.MODE_STREAM
    )
  }

  external fun initHybrid(l: Long): HybridData?

  fun getHybridData(): HybridData? {
    return mHybridData
  }

  override fun start() {
    if(isPlaying) return
    isPlaying = true
    audioTrack.play()
    playbackThread = Thread { generateSound() }.apply{ start()}
  }

  override fun stop() {
    if(!isPlaying) return
    isPlaying = false
    audioTrack.stop()
    playbackThread?.join()
  }

  private fun generateSound() {
    var wavePhase = 0.0
    var phaseChange: Double

    while(isPlaying) {
      phaseChange = 2 * Math.PI * (frequency + detune) / context.sampleRate

      for(i in buffer.indices) {
        buffer[i] = when(waveType) {
          WaveType.SINE -> (sin(wavePhase) * Short.MAX_VALUE).toInt().toShort()
          WaveType.SQUARE -> ((if (sin(wavePhase) >= 0) 1 else -1) * Short.MAX_VALUE).toShort()
          WaveType.SAWTOOTH -> ((2 * (wavePhase / (2 * Math.PI) - floor(wavePhase / (2 * Math.PI) + 0.5))) * Short.MAX_VALUE).toInt().toShort()
          WaveType.TRIANGLE -> ((2 * abs(2 * (wavePhase / (2 * Math.PI) - floor(wavePhase / (2 * Math.PI) + 0.5))) - 1) * Short.MAX_VALUE).toInt().toShort()
        }
        wavePhase += phaseChange
      }

      context.dispatchAudio(buffer, audioTrack)
    }
    audioTrack.flush()
  }
}
