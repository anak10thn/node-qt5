#ifndef QSIZEWRAP_H
#define QSIZEWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include <QSize>

namespace qt5 {

class QSizeWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Local<v8::Object> exports);
  QSize* GetWrapped() const { return q_; };

 private:
  QSizeWrap();
  ~QSizeWrap();
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped methods
  static void Width(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Height(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QSize* q_;
};

}

#endif
