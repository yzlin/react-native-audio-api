#include <jni.h>
#include <jsi/jsi.h>
#include "AudioContextHostObject.h"

using namespace facebook;

void install(jsi::Runtime& runtime) {
    auto hostObject = std::make_shared<audiocontext::AudioContextHostObject>();
    auto object = jsi::Object::createFromHostObject(runtime, hostObject);
    runtime.global().setProperty(runtime, "__JSIExampleProxy", std::move(object));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_audiocontext_jsi_AudioContextModule_00024Companion_nativeInstall(JNIEnv *env, jobject clazz, jlong jsiPtr) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    if (runtime) {
        install(*runtime);
    }
}
