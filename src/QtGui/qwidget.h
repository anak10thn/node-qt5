#ifndef QWIDGETWRAP_H
#define QWIDGETWRAP_H


#include <node.h>
#include <node_object_wrap.h>
#include <QtWidgets/qwidget.h>
#include "nan.h"

namespace qt5 {
//
// QWidgetImpl()
// Extends QWidget to implement virtual methods from QWidget
//
class QWidgetImpl : public QWidget {
 public:
  QWidgetImpl(QWidgetImpl* parent);
  ~QWidgetImpl();
  Nan::Persistent<v8::Value> paintEventCallback_;
  Nan::Persistent<v8::Value> mousePressCallback_;
  Nan::Persistent<v8::Value> mouseReleaseCallback_;
  Nan::Persistent<v8::Value> mouseMoveCallback_;
  Nan::Persistent<v8::Value> keyPressCallback_;
  Nan::Persistent<v8::Value> keyReleaseCallback_;

 private:
  void paintEvent(QPaintEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void keyPressEvent(QKeyEvent* e);
  void keyReleaseEvent(QKeyEvent* e);
};

//
// QWidgetWrap()
//
class QWidgetWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Local<v8::Object> exports);
  QWidgetImpl* GetWrapped() const { return q_; };

 private:
  QWidgetWrap(QWidgetImpl* parent);
  ~QWidgetWrap();
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped methods
  static void Resize(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Show(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Close(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Size(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Width(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Height(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ObjectName(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetObjectName(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Parent(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Update(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetMouseTracking(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void HasMouseTracking(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SetFocusPolicy(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Move(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void X(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Y(const v8::FunctionCallbackInfo<v8::Value>& args);

  // QUIRK
  // Event binding. These functions bind implemented event handlers above
  // to the given callbacks. This is necessary as in Qt such handlers
  // are virtual and we can't dynamically implement them from JS
  static void PaintEvent(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void MousePressEvent(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void MouseReleaseEvent(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void MouseMoveEvent(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void KeyPressEvent(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void KeyReleaseEvent(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QWidgetImpl* q_;
};

}

#endif
