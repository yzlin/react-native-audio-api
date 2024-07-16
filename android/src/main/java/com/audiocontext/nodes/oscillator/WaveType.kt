package com.audiocontext.nodes.oscillator

enum class WaveType {
  SINE,
  SQUARE,
  SAWTOOTH,
  TRIANGLE;

  companion object {
    fun switchWaveType(type: String): WaveType {
      return when (type.uppercase()) {
        "SINE" -> SINE
        "SQUARE" -> SQUARE
        "SAWTOOTH" -> SAWTOOTH
        "TRIANGLE" -> TRIANGLE
        else -> throw IllegalArgumentException("Unknown wave type: $type")
      }
    }
  }
}
