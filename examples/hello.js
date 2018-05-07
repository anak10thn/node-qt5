var qt = require('..'),
    app = new qt.QApplication;
//     window = new qt.QWidget;
//
// // Prevent objects from being GC'd
// global.app = app;
// global.window = window;
//
// window.paintEvent(function(){
//   var p = new qt.QPainter();
//   p.begin(window);
//   p.drawText(20, 30, 'hello node, hello qt');
//   p.end();
// });
//
// window.resize(300, 150);
// window.show();
//
// // Join Node's event loop
setInterval(app.processEvents, 0);
