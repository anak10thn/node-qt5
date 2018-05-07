#include <node.h>
#include "qsize.h"

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

Persistent<Function> QSizeWrap::constructor;

QSizeWrap::QSizeWrap() : q_(NULL) {}

QSizeWrap::~QSizeWrap() {
  delete q_;
}

void QSizeWrap::Initialize(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "QSize"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "width", Width);
  NODE_SET_PROTOTYPE_METHOD(tpl, "height", Height);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "QSize"),
               tpl->GetFunction());
}

void QSizeWrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    QSizeWrap* obj = new QSizeWrap();
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

void QSizeWrap::Width(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QSizeWrap* obj = ObjectWrap::Unwrap<QSizeWrap>(args.This());
  QSize* q = obj->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, q->width()));
}

void QSizeWrap::Height(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QSizeWrap* obj = ObjectWrap::Unwrap<QSizeWrap>(args.This());
  QSize* q = obj->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, q->height()));
}

}
