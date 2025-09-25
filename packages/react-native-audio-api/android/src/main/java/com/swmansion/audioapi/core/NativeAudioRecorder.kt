package com.swmansion.audioapi.core

import com.facebook.common.internal.DoNotStrip
import com.swmansion.audioapi.system.MediaSessionManager

@DoNotStrip
class NativeAudioRecorder {
  private var sourceNodeId: String? = null

  @DoNotStrip
  fun start() {
    this.sourceNodeId = MediaSessionManager.attachAudioRecorder(this)
    MediaSessionManager.startForegroundServiceIfNecessary()
  }

  @DoNotStrip
  fun stop() {
    this.sourceNodeId?.let {
      MediaSessionManager.detachAudioRecorder(it)
      this.sourceNodeId = null
    }
    MediaSessionManager.stopForegroundServiceIfNecessary()
  }
}
