#include <fbjni/fbjni.h>
#include "OscillatorNode.h"
#include "OscillatorNodeHostObject.h"

using namespace audiocontext;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
  return facebook::jni::initialize(vm, [] {
        OscillatorNode::registerNatives();
  });
}
