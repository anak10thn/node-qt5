var qt = require('..'),
    app = new qt.QApplication;

global.app = app;

var hello = new qt.QPushButton('Fuck You Javascript!!!', function () {
    console.log('Hi Javascript Bitch!!');
});
hello.setGeometry(500, 500, 500, 500);
hello.show();

// Start application
app.exec();
