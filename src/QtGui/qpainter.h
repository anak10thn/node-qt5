#ifndef QPAINTERWRAP_H
#define QPAINTERWRAP_H


#include <node.h>
#include <QPainter>

class QPainterWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QPainter* GetWrapped() const { return q_; };

 private:
  QPainterWrap();
  ~QPainterWrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::FunctionCallbackInfo<v8::Value>& args);

  //
  // Wrapped methods exposed to JS
  //

  static v8::Handle<v8::Value> Begin(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> End(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> IsActive(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> Save(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> Restore(const v8::FunctionCallbackInfo<v8::Value>& args);

  // State
  static v8::Handle<v8::Value> SetPen(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> SetFont(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> SetMatrix(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Paint actions
  static v8::Handle<v8::Value> FillRect(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> DrawText(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> DrawPixmap(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> DrawImage(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Handle<v8::Value> StrokePath(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QPainter* q_;
};

#endif
