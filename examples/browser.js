var qt = require('..'),
    app = new qt.QApplication;

global.app = app;

var hello = new qt.QQmlApplicationEngine;
hello.load("examples/browser.qml");
app.exec();
