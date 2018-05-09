#include <node.h>

#include "QtCore/qsize.h"
#include "QtCore/qpointf.h"

#include "QtGui/qapplication.h"
#include "QtGui/qwidget.h"
#include "QtWidgets/qmouseeventtransition.h"
#include "QtWidgets/qkeyeventtransition.h"
#include "QtGui/qpixmap.h"
#include "QtGui/qpainter.h"
#include "QtGui/qcolor.h"
#include "QtGui/qbrush.h"
#include "QtGui/qpen.h"
#include "QtGui/qimage.h"
#include "QtGui/qpainterpath.h"
#include "QtGui/qfont.h"
#include "QtGui/qmatrix.h"

#include "QtMultimedia/qsound.h"

#include "QtWidgets/qscrollarea.h"
#include "QtWidgets/qscrollbar.h"
#include "QtWidgets/qpushbutton.h"

#include "QtTest/qtesteventlist.h"

#include "QtQml/qqmlapplicationengine.h"

namespace qt5 {

using v8::Local;
using v8::Object;


void Initialize(Local<Object> target) {
  QApplicationWrap::Initialize(target);
  // QWidgetWrap::Initialize(target);
  QPushButtonWrap::Initialize(target);
  QSizeWrap::Initialize(target);
  QQmlApplicationEngineWrap::Initialize(target);
  // QMouseEventWrap::Initialize(target);
  // QKeyEventWrap::Initialize(target);
  // QTestEventListWrap::Initialize(target);
  // QPixmapWrap::Initialize(target);
  // QPainterWrap::Initialize(target);
  // QColorWrap::Initialize(target);
  // QBrushWrap::Initialize(target);
  // QPenWrap::Initialize(target);
  // QImageWrap::Initialize(target);
  // QPointFWrap::Initialize(target);
  // QPainterPathWrap::Initialize(target);
  // QFontWrap::Initialize(target);
  // QMatrixWrap::Initialize(target);
  // QSoundWrap::Initialize(target);
  // QScrollAreaWrap::Initialize(target);
  // QScrollBarWrap::Initialize(target);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}
