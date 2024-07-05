#include <jni.h>
#include "react-native-audio-context.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_audiocontext_AudioContextModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return audiocontext::multiply(a, b);
}
