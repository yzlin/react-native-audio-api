package com.audiocontext.jsi

import android.util.Log
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.module.annotations.ReactModule

@ReactModule(name = JSIExampleModule.NAME)
class JSIExampleModule(reactContext: ReactApplicationContext?) :
  ReactContextBaseJavaModule(reactContext) {
  override fun getName(): String {
    return NAME
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  fun install(): Boolean {
    try {
      System.loadLibrary("react-native-audio-context")

      val jsContext = reactApplicationContext.javaScriptContextHolder

      nativeInstall(jsContext!!.get())
      return true
    } catch (exception: Exception) {
      Log.e(NAME, "Failed to install JSI Bindings for react-native-audio-context", exception)
      return false
    }
  }

  companion object {
    const val NAME: String = "JSIExample"

    private external fun nativeInstall(jsiPtr: Long)
  }
}
