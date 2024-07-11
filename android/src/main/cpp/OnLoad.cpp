#include <fbjni/fbjni.h>
#include "Oscillator.h"
#include "OscillatorHostObject.h"

using namespace audiocontext;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
  return facebook::jni::initialize(vm, [] {
        Oscillator::registerNatives();
  });
}
