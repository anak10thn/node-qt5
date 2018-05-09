var qt = require('..'),
    app = new qt.QApplication;

global.app = app;

var hello = new qt.QQmlApplicationEngine;
console.log(process.cwd())
hello.load("examples/test.qml");

// Start application
app.exec();
