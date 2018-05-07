#include <node.h>
#include "../qt_v8.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qcolor.h"
#include "qpen.h"
#include "qwidget.h"
#include "qbrush.h"
#include "qimage.h"
#include "qpainterpath.h"
#include "qfont.h"
#include "qmatrix.h"

using namespace v8;

Persistent<Function> QPainterWrap::constructor;

QPainterWrap::QPainterWrap() {
  q_ = new QPainter();
}
QPainterWrap::~QPainterWrap() {
  delete q_;
}

void QPainterWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QPainter"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("begin"),
      FunctionTemplate::New(Begin)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("end"),
      FunctionTemplate::New(End)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("isActive"),
      FunctionTemplate::New(IsActive)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("save"),
      FunctionTemplate::New(Save)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("restore"),
      FunctionTemplate::New(Restore)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPen"),
      FunctionTemplate::New(SetPen)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setFont"),
      FunctionTemplate::New(SetFont)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setMatrix"),
      FunctionTemplate::New(SetMatrix)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("fillRect"),
      FunctionTemplate::New(FillRect)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("drawText"),
      FunctionTemplate::New(DrawText)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("drawPixmap"),
      FunctionTemplate::New(DrawPixmap)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("drawImage"),
      FunctionTemplate::New(DrawImage)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("strokePath"),
      FunctionTemplate::New(StrokePath)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QPainter"), constructor);
}

Handle<Value> QPainterWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args) {


  if (args.Length()>0) {
    return ThrowException(Exception::TypeError(
        String::New("QPainterWrap: use begin() for initialization")));
  }

  QPainterWrap* w = new QPainterWrap();
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QPainterWrap::Begin(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  if (!args[0]->IsObject())
    return ThrowException(Exception::TypeError(
        String::New("QPainterWrap:Begin: bad arguments")));

  QString constructor_name =
    qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());

  // Determine argument type (from its constructor) so we can unwrap it
  if (constructor_name == "QPixmap") {
    // QPixmap
    QPixmapWrap* pixmap_wrap = ObjectWrap::Unwrap<QPixmapWrap>(
        args[0]->ToObject());
    QPixmap* pixmap = pixmap_wrap->GetWrapped();

    return scope.Close(Boolean::New( q->begin(pixmap) ));
  } else if (constructor_name == "QWidget") {
    // QWidget
    QWidgetWrap* widget_wrap = ObjectWrap::Unwrap<QWidgetWrap>(
        args[0]->ToObject());
    QWidget* widget = widget_wrap->GetWrapped();

    return scope.Close(Boolean::New( q->begin(widget) ));
  }

  // Unknown argument type
  return scope.Close(Boolean::New( false ));
}

Handle<Value> QPainterWrap::End(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  return scope.Close(Boolean::New( q->end() ));
}

Handle<Value> QPainterWrap::IsActive(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  return scope.Close(Boolean::New( q->isActive() ));
}

Handle<Value> QPainterWrap::Save(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  q->save();

  return scope.Close(Undefined());
}

Handle<Value> QPainterWrap::Restore(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  q->restore();

  return scope.Close(Undefined());
}

// Supported implementations:
//   setPen( QPen pen )
Handle<Value> QPainterWrap::SetPen(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  QString arg0_constructor;
  if (args[0]->IsObject()) {
    arg0_constructor =
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());
  }

  if (arg0_constructor != "QPen")
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::SetPen: bad argument")));

  // Unwrap obj
  QPenWrap* pen_wrap = ObjectWrap::Unwrap<QPenWrap>(
      args[0]->ToObject());
  QPen* pen = pen_wrap->GetWrapped();

  q->setPen(*pen);

  return scope.Close(Undefined());
}

Handle<Value> QPainterWrap::SetFont(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  QString arg0_constructor;
  if (args[0]->IsObject()) {
    arg0_constructor =
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());
  }

  if (arg0_constructor != "QFont")
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::SetFont: bad argument")));

  // Unwrap obj
  QFontWrap* font_wrap = ObjectWrap::Unwrap<QFontWrap>(
      args[0]->ToObject());
  QFont* font = font_wrap->GetWrapped();

  q->setFont(*font);

  return scope.Close(Undefined());
}

// This seems to be undocumented in Qt, but it exists!
Handle<Value> QPainterWrap::SetMatrix(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  QString arg0_constructor;
  if (args[0]->IsObject()) {
    arg0_constructor =
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());
  }

  if (arg0_constructor != "QMatrix")
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::SetMatrix: bad argument")));

  // Unwrap obj
  QMatrixWrap* matrix_wrap = ObjectWrap::Unwrap<QMatrixWrap>(
      args[0]->ToObject());
  QMatrix* matrix = matrix_wrap->GetWrapped();

  q->setMatrix(*matrix, args[1]->BooleanValue());

  return scope.Close(Undefined());
}

// Supported versions:
//   fillRect(int x, int y, int w, int h, QBrush brush)
//   fillRect(int x, int y, int w, int h, QColor color)
//   fillRect(int x, int y, int w, int h, Qt::GlobalColor color)
Handle<Value> QPainterWrap::FillRect(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() ||
      !args[3]->IsNumber())
    return scope.Close(Undefined());

  QString arg4_constructor;
  if (args[4]->IsObject()) {
    arg4_constructor =
        qt_v8::ToQString(args[4]->ToObject()->GetConstructorName());
  }

  if (arg4_constructor == "QBrush") {
    // fillRect(int x, int y, int w, int h, QBrush brush)

    // Unwrap QBrush
    QBrushWrap* brush_wrap = ObjectWrap::Unwrap<QBrushWrap>(
        args[4]->ToObject());
    QBrush* brush = brush_wrap->GetWrapped();

    q->fillRect(args[0]->IntegerValue(), args[1]->IntegerValue(),
                args[2]->IntegerValue(), args[3]->IntegerValue(),
                *brush);
  } else if (arg4_constructor == "QColor") {
    // fillRect(int x, int y, int w, int h, QColor color)

    // Unwrap QColor
    QColorWrap* color_wrap = ObjectWrap::Unwrap<QColorWrap>(
        args[4]->ToObject());
    QColor* color = color_wrap->GetWrapped();

    q->fillRect(args[0]->IntegerValue(), args[1]->IntegerValue(),
                args[2]->IntegerValue(), args[3]->IntegerValue(),
                *color);
  } else if (args[4]->IsNumber()) {
    // fillRect(int x, int y, int w, int h, Qt::GlobalColor color)

    q->fillRect(args[0]->IntegerValue(), args[1]->IntegerValue(),
                args[2]->IntegerValue(), args[3]->IntegerValue(),
                (Qt::GlobalColor)args[4]->IntegerValue());
  } else {
    return ThrowException(Exception::TypeError(
        String::New("QPainterWrap:fillRect: bad arguments")));
  }

  return scope.Close(Undefined());
}

// Supported versions:
//   drawText(int x, int y, "text")
Handle<Value> QPainterWrap::DrawText(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsString())
    return ThrowException(Exception::TypeError(
        String::New("QPainterWrap:DrawText: bad arguments")));

  q->drawText(args[0]->IntegerValue(), args[1]->IntegerValue(),
      qt_v8::ToQString(args[2]->ToString()));

  return scope.Close(Undefined());
}

// Supported versions:
//   drawPixmap(int x, int y, QPixmap pixmap)
Handle<Value> QPainterWrap::DrawPixmap(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  QString arg2_constructor;
  if (args[2]->IsObject()) {
    arg2_constructor =
        qt_v8::ToQString(args[2]->ToObject()->GetConstructorName());
  }

  if (arg2_constructor != "QPixmap" ) {
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::DrawPixmap: pixmap argument not recognized")));
  }

  // Unwrap QPixmap
  QPixmapWrap* pixmap_wrap = ObjectWrap::Unwrap<QPixmapWrap>(
      args[2]->ToObject());
  QPixmap* pixmap = pixmap_wrap->GetWrapped();

  if (pixmap->isNull()) {
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::DrawPixmap: pixmap is null, no size set?")));
  }

  q->drawPixmap(args[0]->IntegerValue(), args[1]->IntegerValue(), *pixmap);

  return scope.Close(Undefined());
}

// Supported versions:
//   drawImage( int x, int y, QImage image )
Handle<Value> QPainterWrap::DrawImage(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  QString arg2_constructor;
  if (args[2]->IsObject()) {
    arg2_constructor =
        qt_v8::ToQString(args[2]->ToObject()->GetConstructorName());
  }

  if (arg2_constructor != "QImage" ) {
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::DrawImage: image argument not recognized")));
  }

  // Unwrap QImage
  QImageWrap* image_wrap = ObjectWrap::Unwrap<QImageWrap>(
      args[2]->ToObject());
  QImage* image = image_wrap->GetWrapped();

  if (image->isNull()) {
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::DrawImage: image is null, no size set?")));
  }

  q->drawImage(args[0]->IntegerValue(), args[1]->IntegerValue(), *image);

  return scope.Close(Undefined());
}

// Supported versions:
//   strokePath( QPainterPath path, QPen pen )
Handle<Value> QPainterWrap::StrokePath(const v8::FunctionCallbackInfo<v8::Value>& args) {


  QPainterWrap* w = ObjectWrap::Unwrap<QPainterWrap>(args.This());
  QPainter* q = w->GetWrapped();

  QString arg0_constructor;
  if (args[0]->IsObject()) {
    arg0_constructor =
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());
  }

  if (arg0_constructor != "QPainterPath" ) {
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::StrokePath: bad arguments")));
  }

  QString arg1_constructor;
  if (args[1]->IsObject()) {
    arg1_constructor =
        qt_v8::ToQString(args[1]->ToObject()->GetConstructorName());
  }

  if (arg1_constructor != "QPen" ) {
    return ThrowException(Exception::TypeError(
      String::New("QPainterWrap::StrokePath: bad arguments")));
  }

  // Unwrap QPainterPath
  QPainterPathWrap* path_wrap = ObjectWrap::Unwrap<QPainterPathWrap>(
      args[0]->ToObject());
  QPainterPath* path = path_wrap->GetWrapped();

  // Unwrap QPen
  QPenWrap* pen_wrap = ObjectWrap::Unwrap<QPenWrap>(
      args[1]->ToObject());
  QPen* pen = pen_wrap->GetWrapped();

  q->strokePath(*path, *pen);

  return scope.Close(Undefined());
}
