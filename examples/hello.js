var qt = require('..'),
    app = new qt.QApplication;

global.app = app;

var hello = new qt.QPushButton('Hello World', function () {
    console.log('hi');
});
hello.setGeometry(500, 500, 500, 500);
hello.show();

var hello = new qt.QPushButton('Hello World', function () {
    console.log('hi');
});
hello.setGeometry(500, 500, 500, 500);
hello.show();

// Start application
app.exec();
