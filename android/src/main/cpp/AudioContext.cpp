#include "AudioContext.h"
#include "AudioContextHostObject.h"
#include "OscillatorNode.h"
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

namespace audiocontext {

    using namespace facebook::jni;

    AudioContext::AudioContext(jni::alias_ref<AudioContext::jhybridobject> &jThis,
                                   jlong jsContext): javaObject_(make_global(jThis)) {
        auto runtime = reinterpret_cast<jsi::Runtime *>(jsContext);
        auto hostObject = std::make_shared<AudioContextHostObject>(this);
        auto object = jsi::Object::createFromHostObject(*runtime, hostObject);
        auto createOscillatorFunction = jsi::Function::createFromHostFunction(
                *runtime,
                jsi::PropNameID::forAscii(*runtime, "createOscillator"),
                0,
                [this](jsi::Runtime &runtime, const jsi::Value &, const jsi::Value *, size_t) {
                    return jsiCreateOscillator(runtime);
                });
        object.setProperty(*runtime, "createOscillator", std::move(createOscillatorFunction));
        runtime->global().setProperty(*runtime, "__AudioContextProxy", std::move(object));
    }

    // this method is called from Java to create a new instance of oscillator
    jni::local_ref<OscillatorNode::jhybriddata> AudioContext::createOscillator() {
        auto method = javaClassStatic()->getMethod<jni::local_ref<OscillatorNode::jhybriddata>()>("createOscillator");
        return method(javaObject_.get());
    }

    // this method is called in order to get a reference to c++ hybrid object of oscillator
    //and create a host object for it
    jsi::Value AudioContext::jsiCreateOscillator(jsi::Runtime &runtime) {
        auto oscillatorHybridData = createOscillator();
        auto oscillatorNode = oscillatorHybridData->cthis();//error detail::HybridData does not have a member named 'cthis'
        //cthis() is a method of HybridClass class that returns a pointer to the c++ object

        //HybridClass from Hybrid.h
        //template <typename T, typename Base = detail::BaseHybridClass>
        //class HybridClass : public detail::HybridTraits<Base>::CxxBase {
        // public:
        //  struct JavaPart
        //      : JavaClass<JavaPart, typename detail::HybridTraits<Base>::JavaBase> {
        //    // At this point, T is incomplete, and so we cannot access
        //    // T::kJavaDescriptor directly. jtype_traits support this escape hatch for
        //    // such a case.
        //    static constexpr const char* kJavaDescriptor = nullptr;
        //    static constexpr auto /* detail::SimpleFixedString<_> */
        //    get_instantiated_java_descriptor();
        //    static constexpr auto /* detail::SimpleFixedString<_> */
        //    get_instantiated_base_name();
        //
        //    using HybridType = T;
        //
        //    // This will reach into the java object and extract the C++ instance from
        //    // the mHybridData and return it.
        //    T* cthis() const;
        //
        //    friend class HybridClass;
        //    friend T;
        //  };
        return oscillatorNode->createOscillatorNodeHostObject(runtime);
    }

} // namespace audiocontext
