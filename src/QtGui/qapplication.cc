#include <node.h>
#include "qapplication.h"

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

Persistent<Function> QApplicationWrap::constructor;

int QApplicationWrap::argc_ = 0;
char** QApplicationWrap::argv_ = NULL;

QApplicationWrap::QApplicationWrap() {
  q_ = new QApplication(argc_, argv_);
}

QApplicationWrap::~QApplicationWrap() {
  delete q_;
}

void QApplicationWrap::Initialize(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "QApplication"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "processEvents", ProcessEvents);
  NODE_SET_PROTOTYPE_METHOD(tpl, "exec", Exec);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "QApplication"),
               tpl->GetFunction());
}

void QApplicationWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.IsConstructCall()) {
    QApplicationWrap* obj = new QApplicationWrap();
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

void QApplicationWrap::ProcessEvents(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->processEvents();

  args.GetReturnValue().Set(Undefined(isolate));
}

void QApplicationWrap::Exec(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->exec();

  args.GetReturnValue().Set(Undefined(isolate));
}

}
