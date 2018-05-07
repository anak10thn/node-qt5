#include <node.h>
#include "../qt_v8.h"
#include "../QtCore/qsize.h"
#include "qwidget.h"
#include "QtWidgets/qmouseeventtransition.h"
#include "QtWidgets/qkeyeventtransition.h"
#include "qmouseevent.h"
#include "qkeyevent.h"
#include "nan.h"

namespace qt5 {

// using namespace v8;
using namespace Nan;

v8::Persistent<v8::Function> QWidgetWrap::constructor;

//
// QWidgetImpl()
//

QWidgetImpl::QWidgetImpl(QWidgetImpl* parent) : QWidget(parent) {
  // Initialize callbacks as boolean values so we can test if the callback
  // has been set via ->IsFunction() below
  Persistent<v8::Boolean> persistent(Nan::False());
  paintEventCallback_.Reset(persistent);
  mousePressCallback_.Reset(persistent);
  mouseReleaseCallback_.Reset(persistent);
  mouseMoveCallback_.Reset(persistent);
  keyPressCallback_.Reset(persistent);
  keyReleaseCallback_.Reset(persistent);
  persistent.Reset();
  // paintEventCallback_ = Persistent<v8::Boolean>::New(Isolate::GetCurrent(), Boolean::New(Isolate::GetCurrent(),false));
  // mousePressCallback_ = Persistent<Boolean>::New(Isolate::GetCurrent(), Boolean::New(false));
  // mouseReleaseCallback_ = Persistent<Boolean>::New(Isolate::GetCurrent(), Boolean::New(false));
  // mouseMoveCallback_ = Persistent<Boolean>::New(Isolate::GetCurrent(), Boolean::New(false));
  // keyPressCallback_ = Persistent<Boolean>::New(Isolate::GetCurrent(), Boolean::New(false));
  // keyReleaseCallback_ = Persistent<Boolean>::New(Isolate::GetCurrent(), Boolean::New(false));
}

QWidgetImpl::~QWidgetImpl() {
  paintEventCallback_.Reset();
  mousePressCallback_.Reset();
  mouseReleaseCallback_.Reset();
  mouseMoveCallback_.Reset();
  keyPressCallback_.Reset();
  keyReleaseCallback_.Reset();
}

void QWidgetImpl::paintEvent(QPaintEvent* e) {
  v8::Isolate * isolate = v8::Isolate::GetCurrent();
  // if (!paintEventCallback_->IsFunction())
  //   return;

  const unsigned argc = 0;
  v8::Handle<v8::Value> argv[1] = {};

  v8::Handle<v8::Function> cb = v8::Local<v8::Function>::New(isolate, v8::Persistent<v8::Function>::Cast(paintEventCallback_));

  cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

void QWidgetImpl::mousePressEvent(QMouseEvent* e) {
  //e->ignore(); // ensures event bubbles up



  // if (!mousePressCallback_->IsFunction())
  //   return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QMouseEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(mousePressCallback_);

  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::mouseReleaseEvent(QMouseEvent* e) {
  e->ignore(); // ensures event bubbles up



  // if (!mouseReleaseCallback_->IsFunction())
  //   return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QMouseEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(mouseReleaseCallback_);

  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::mouseMoveEvent(QMouseEvent* e) {
  e->ignore(); // ensures event bubbles up



  // if (!mouseMoveCallback_->IsFunction())
  //   return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QMouseEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(mouseMoveCallback_);

  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::keyPressEvent(QKeyEvent* e) {
  e->ignore(); // ensures event bubbles up



  // if (!keyPressCallback_->IsFunction())
  //   return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QKeyEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(keyPressCallback_);

  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::keyReleaseEvent(QKeyEvent* e) {
  e->ignore(); // ensures event bubbles up



  // if (!keyReleaseCallback_->IsFunction())
  //   return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QKeyEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(keyReleaseCallback_);

  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

//
// QWidgetWrap()
//

QWidgetWrap::QWidgetWrap(QWidgetImpl* parent) {
  q_ = new QWidgetImpl(parent);
}

QWidgetWrap::~QWidgetWrap() {
  delete q_;
}

void QWidgetWrap::Initialize(Handle<Object> target) {
  Isolate* isolate = exports->GetIsolate();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "QWidget"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Wrapped methods
  NODE_SET_PROTOTYPE_METHOD(tpl, "resize", Resize);
  NODE_SET_PROTOTYPE_METHOD(tpl, "show", Show);
  NODE_SET_PROTOTYPE_METHOD(tpl, "close", Close);
  NODE_SET_PROTOTYPE_METHOD(tpl, "size", Size);
  NODE_SET_PROTOTYPE_METHOD(tpl, "width", Width);
  NODE_SET_PROTOTYPE_METHOD(tpl, "height", Height);
  NODE_SET_PROTOTYPE_METHOD(tpl, "parent", Parent);
  NODE_SET_PROTOTYPE_METHOD(tpl, "objectName", ObjectName);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setObjectName", SetObjectName);
  NODE_SET_PROTOTYPE_METHOD(tpl, "update", Update);
  NODE_SET_PROTOTYPE_METHOD(tpl, "hasMouseTracking", HasMouseTracking);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setMouseTracking", SetMouseTracking);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setFocusPolicy", SetFocusPolicy);
  NODE_SET_PROTOTYPE_METHOD(tpl, "move", Move);
  NODE_SET_PROTOTYPE_METHOD(tpl, "x", X);
  NODE_SET_PROTOTYPE_METHOD(tpl, "y", Y);

  // Events
  NODE_SET_PROTOTYPE_METHOD(tpl, "paintEvent", PaintEvent);
  NODE_SET_PROTOTYPE_METHOD(tpl, "mousePressEvent", MousePressEvent);
  NODE_SET_PROTOTYPE_METHOD(tpl, "mouseReleaseEvent", MouseReleaseEvent);
  NODE_SET_PROTOTYPE_METHOD(tpl, "mouseMoveEvent", MouseMoveEvent);
  NODE_SET_PROTOTYPE_METHOD(tpl, "keyPressEvent", KeyPressEvent);
  NODE_SET_PROTOTYPE_METHOD(tpl, "keyReleaseEvent", KeyReleaseEvent);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "QWidget"),
               tpl->GetFunction());
}

void QWidgetWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    QWidgetImpl* q_parent = 0;

    if (args.Length() > 0) {
      QWidgetWrap* w_parent = node::ObjectWrap::Unwrap<QWidgetWrap>(args[0]->ToObject());
      q_parent = w_parent->GetWrapped();
    }

    QWidgetWrap* w = new QWidgetWrap(q_parent);
    w->Wrap(args.This());
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

void QWidgetWrap::Resize(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->resize(args[0]->NumberValue(), args[1]->NumberValue());

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::Show(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->show();

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::Close(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->close();

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::Size(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, QSizeWrap::New(q->size())));
}

void QWidgetWrap::Width(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, Integer::New(q->width())));
}

void QWidgetWrap::Height(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, Integer::New(q->height())));
}

void QWidgetWrap::ObjectName(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, qt_v8::FromQString(q->objectName())));
}

void QWidgetWrap::SetObjectName(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->setObjectName(qt_v8::ToQString(args[0]->ToString()));

  args.GetReturnValue().Set(Undefined(isolate));
}

//
// QUIRK:
// Here: Parent() returns the parent's name
// Qt: Parent() returns QObject
// Intended mostly for sanity checks
//
void QWidgetWrap::Parent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  rgs.GetReturnValue().Set(Number::New(isolate, qt_v8::FromQString(q->parent()->objectName())));
}

//
// PaintEvent()
// Binds a callback to Qt's event
//
void QWidgetWrap::PaintEvent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->paintEventCallback_.Reset();
  q->paintEventCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  args.GetReturnValue().Set(Undefined(isolate));
}

//
// MousePressEvent()
// Binds a callback to Qt's event
//
void QWidgetWrap::MousePressEvent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->mousePressCallback_.Reset();
  q->mousePressCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  args.GetReturnValue().Set(Undefined(isolate));
}

//
// MouseReleaseEvent()
// Binds a callback to Qt's event
//
void QWidgetWrap::MouseReleaseEvent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->mouseReleaseCallback_.Reset();
  q->mouseReleaseCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  args.GetReturnValue().Set(Undefined(isolate));
}

//
// MouseMoveEvent()
// Binds a callback to Qt's event
//
void QWidgetWrap::MouseMoveEvent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->mouseMoveCallback_.Reset();
  q->mouseMoveCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  args.GetReturnValue().Set(Undefined(isolate));
}

//
// KeyPressEvent()
// Binds a callback to Qt's event
//
void QWidgetWrap::KeyPressEvent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->keyPressCallback_.Reset();
  q->keyPressCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  args.GetReturnValue().Set(Undefined(isolate));
}

//
// KeyReleaseEvent()
// Binds a callback to Qt's event
//
void QWidgetWrap::KeyReleaseEvent(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->keyReleaseCallback_.Reset();
  q->keyReleaseCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::Update(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->update();

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::HasMouseTracking(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->hasMouseTracking()));
}

void QWidgetWrap::SetMouseTracking(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->setMouseTracking(args[0]->BooleanValue());

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::SetFocusPolicy(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->setFocusPolicy((Qt::FocusPolicy)(args[0]->IntegerValue()));

  args.GetReturnValue().Set(Undefined(isolate));
}

// Supported implementations:
//    move (int x, int y)
void QWidgetWrap::Move(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->move(args[0]->IntegerValue(), args[1]->IntegerValue());

  args.GetReturnValue().Set(Undefined(isolate));
}

void QWidgetWrap::X(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, q->x()));
}

void QWidgetWrap::Y(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  args.GetReturnValue().Set(Number::New(isolate, q->y()));
}

}
