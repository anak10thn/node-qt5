#include <node.h>
#include "qqmlapplicationengine.h"
#include "../qt_v8.h"

namespace qt5 {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

Persistent<Function> QQmlApplicationEngineWrap::constructor;

QQmlApplicationEngineWrap::QQmlApplicationEngineWrap() {
  q_ = new QQmlApplicationEngine();
}

QQmlApplicationEngineWrap::~QQmlApplicationEngineWrap() {
  delete q_;
}

void QQmlApplicationEngineWrap::Initialize(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "QQmlApplicationEngine"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "load", Load);
  NODE_SET_PROTOTYPE_METHOD(tpl, "rootObjects", RootObjects);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "QQmlApplicationEngine"),
               tpl->GetFunction());
}

void QQmlApplicationEngineWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.IsConstructCall()) {
    QQmlApplicationEngineWrap* obj = new QQmlApplicationEngineWrap();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

void QQmlApplicationEngineWrap::Load(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QQmlApplicationEngineWrap* w = ObjectWrap::Unwrap<QQmlApplicationEngineWrap>(args.This());
  QQmlApplicationEngine* q = w->GetWrapped();

  q->load(qt_v8::ToQString(args[0]->ToString()));

  args.GetReturnValue().Set(Undefined(isolate));
}

void QQmlApplicationEngineWrap::RootObjects(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QQmlApplicationEngineWrap* w = ObjectWrap::Unwrap<QQmlApplicationEngineWrap>(args.This());
  QQmlApplicationEngine* q = w->GetWrapped();

  q->rootObjects();

  args.GetReturnValue().Set(Undefined(isolate));
}

}
