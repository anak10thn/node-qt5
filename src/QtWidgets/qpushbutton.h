#ifndef QPushButtonWRAP_H
#define QPushButtonWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include <QPushButton>

class QPushButtonWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Local<v8::Object> exports);
  QPushButton* GetWrapped() const { return q_; };

 private:
  QPushButtonWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  ~QPushButtonWrap();
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped methods
  static void SetGeometry(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetObjectName(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Show(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QPushButton* q_;
  static int argc_;
  static char** argv_;
};

#endif