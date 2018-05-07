#ifndef QAPPLICATIONWRAP_H
#define QAPPLICATIONWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include <QApplication>

namespace qt5 {

class QApplicationWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QApplication* GetWrapped() const { return q_; };

 private:
  QApplicationWrap();
  ~QApplicationWrap();
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped methods
  static void ProcessEvents(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Exec(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetStyleSheet(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QApplication* q_;
  static int argc_;
  static char** argv_;
};

}

#endif
