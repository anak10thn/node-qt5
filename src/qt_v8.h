#ifndef QTV8_H
#define QTV8_H

#include <node.h>
#include <QString>

namespace qt_v8 {

inline QString ToQString(v8::Local<v8::String> str) {
  return QString::fromUtf16( *v8::String::Value(v8::Isolate::GetCurrent(), str) );
}

inline v8::Local<v8::String> FromQString(QString str) {
  return v8::String::NewFromTwoByte(v8::Isolate::GetCurrent(),str.utf16());
}

} // namespace

#endif
