#pragma once

#include <audioapi/jsi/RuntimeAwareCache.h>

#include <jsi/jsi.h>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define JSI_HOST_FUNCTION_DECL(name) jsi::Value name(jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *args, size_t count)
#define JSI_HOST_FUNCTION_IMPL(CLASS, name) jsi::Value CLASS::name(jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *args, size_t count)
#define JSI_EXPORT_FUNCTION(CLASS, FUNCTION)                                \
  std::make_pair(                                                           \
      std::string(#FUNCTION),                                               \
      static_cast<jsi::Value (JsiHostObject::*)(                            \
          jsi::Runtime &, const jsi::Value &, const jsi::Value *, size_t)>( \
          &CLASS::FUNCTION))

#define JSI_PROPERTY_GETTER_DECL(name) jsi::Value name(jsi::Runtime &runtime)
#define JSI_PROPERTY_GETTER_IMPL(CLASS, name) jsi::Value CLASS::name(jsi::Runtime &runtime)
#define JSI_EXPORT_PROPERTY_GETTER(CLASS, FUNCTION)               \
  std::make_pair(                                                 \
      std::string(#FUNCTION),                                     \
      static_cast<jsi::Value (JsiHostObject::*)(jsi::Runtime &)>( \
          &CLASS::FUNCTION))

#define JSI_PROPERTY_SETTER_DECL(name) void name(jsi::Runtime &runtime, const jsi::Value &value)
#define JSI_PROPERTY_SETTER_IMPL(CLASS, name) void CLASS::name(jsi::Runtime &runtime, const jsi::Value &value)
#define JSI_EXPORT_PROPERTY_SETTER(CLASS, FUNCTION) \
  std::make_pair(                                   \
      std::string(#FUNCTION),                       \
      static_cast<void (JsiHostObject::*)(          \
          jsi::Runtime &, const jsi::Value &)>(&CLASS::FUNCTION))

namespace audioapi {

using namespace facebook;

class JsiHostObject : public jsi::HostObject {
 public:
  JsiHostObject();
  JsiHostObject(const JsiHostObject &) = delete;
  JsiHostObject &operator=(const JsiHostObject &) = delete;
  JsiHostObject(JsiHostObject &&) noexcept;
  JsiHostObject &operator=(JsiHostObject &&other) noexcept;
  ~JsiHostObject() override;

  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

  jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;

  void set(
      jsi::Runtime &runtime,
      const jsi::PropNameID &name,
      const jsi::Value &value) override;

  template <typename... Args>
  void addGetters(Args... args) {
    (getters_->insert(args), ...);
  }

  template <typename... Args>
  void addSetters(Args... args) {
    (setters_->insert(args), ...);
  }

  template <typename... Args>
  void addFunctions(Args... args) {
    (functions_->insert(args), ...);
  }

 protected:
  std::unique_ptr<std::unordered_map<
      std::string,
      jsi::Value (JsiHostObject::*)(jsi::Runtime &)>>
      getters_;

  std::unique_ptr<std::unordered_map<
      std::string,
      jsi::Value (JsiHostObject::*)(
          jsi::Runtime &,
          const jsi::Value &,
          const jsi::Value *,
          size_t)>>
      functions_;

  std::unique_ptr<std::unordered_map<
      std::string,
      void (JsiHostObject::*)(jsi::Runtime &, const jsi::Value &)>>
      setters_;

 private:
  RuntimeAwareCache<std::map<std::string, jsi::Function>> hostFunctionCache_;
};

} // namespace audioapi
