#include <node.h>
#include "qpushbutton.h"
#include "../qt_v8.h"
// #include "nan.h"

using namespace v8;

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

Persistent<Function> QPushButtonWrap::constructor;

int QPushButtonWrap::argc_ = 0;
char** QPushButtonWrap::argv_ = NULL;

//
// QPushButtonWrap()
//

/**
 * new QPushButton('Button Text', function() {
 *   console.log("I've been clicked!");
 * });
 */
QPushButtonWrap::QPushButtonWrap(const v8::FunctionCallbackInfo<v8::Value>& args){
    Isolate * isolate = Isolate::GetCurrent();
    if (args[0]->IsString()) {
        // QPushButton ( QPushButton Text )
        q_ = new QPushButton(qt_v8::ToQString(args[0]->ToString()));
    } else {
        q_ = new QPushButton();
    }

    if (args[1]->IsFunction()) {
        Handle<Function> cb = v8::Local<v8::Function>::New(isolate, Local<Function>::Cast(args[1]));

        QObject::connect(q_, &QPushButton::clicked, [=]() {
            const unsigned argc = 0;
            Handle<Value> argv[1] = {};
            cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
        });
    }
}

QPushButtonWrap::~QPushButtonWrap() {
  delete q_;
}

void QPushButtonWrap::Initialize(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "QPushButton"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectName", SetObjectName);
    NODE_SET_PROTOTYPE_METHOD(tpl, "show", Show);
    NODE_SET_PROTOTYPE_METHOD(tpl, "setGeometry", SetGeometry);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "QPushButton"),
                tpl->GetFunction());
}

void QPushButtonWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.IsConstructCall()) {
    QPushButtonWrap* obj = new QPushButtonWrap(args);
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

void QPushButtonWrap::Show(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QPushButtonWrap* w = ObjectWrap::Unwrap<QPushButtonWrap>(args.This());
  QPushButton* q = w->GetWrapped();

  q->show();

  args.GetReturnValue().Set(Undefined(isolate));
}

void QPushButtonWrap::SetGeometry(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QPushButtonWrap* w = ObjectWrap::Unwrap<QPushButtonWrap>(args.This());
  QPushButton* q = w->GetWrapped();

//   if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() ||
//       !args[3]->IsNumber())
    // return ThrowException(Exception::TypeError(
    //     String(isolate, "QPushButtonWrap:setGeometry: bad arguments")));

  q->setGeometry(args[0]->IntegerValue(), args[1]->IntegerValue(),
                args[2]->IntegerValue(), args[3]->IntegerValue());

   args.GetReturnValue().Set(Undefined(isolate));
}

void QPushButtonWrap::SetObjectName(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QPushButtonWrap* w = ObjectWrap::Unwrap<QPushButtonWrap>(args.This());
  QPushButton* q = w->GetWrapped();

//   if (!args[0]->IsString())
//     return ThrowException(Exception::TypeError(
//         String::New("QPushButton:setObjectName: bad argument")));

  q->setObjectName(qt_v8::ToQString(args[0]->ToString()));

  args.GetReturnValue().Set(Undefined(isolate));
}