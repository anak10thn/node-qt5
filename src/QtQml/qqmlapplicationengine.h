#ifndef QQMLAPPLICATIONENGINEWRAP_H
#define QQMLAPPLICATIONENGINEWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include <QQmlApplicationEngine>

namespace qt5 {

class QQmlApplicationEngineWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QQmlApplicationEngine* GetWrapped() const { return q_; };

 private:
  QQmlApplicationEngineWrap();
  ~QQmlApplicationEngineWrap();
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped methods
  static void Load(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void RootObjects(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QQmlApplicationEngine* q_;
};

}

#endif
