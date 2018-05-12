{
    'targets': [{
        'target_name':
        'qt5',
        'sources': [
            'src/qt.cc',
            'src/QtCore/qsize.cc',
            # 'src/QtCore/qpointf.cc',
            #
            'src/QtGui/qapplication.cc',
            # 'src/QtGui/qwidget.cc'
            # 'src/QtGui/qpainter.cc'
            #
            # 'src/QtTest/qtesteventlist.cc',
            'src/QtWidgets/qpushbutton.cc',
            'src/QtQml/qqmlapplicationengine.cc'
        ],
        'conditions': [
            ['OS=="mac"', {
                'xcode_settings': {
                    'LD_RUNPATH_SEARCH_PATHS': [
                        '@excutable_path/deps/qt-5.10.1/darwin/x64/Frameworks',
                        '@loader_path/deps/qt-5.10.1/darwin/x64/Frameworks',
                        '@excutable_path/../deps/qt-5.10.1/darwin/x64/Frameworks',
                        '@loader_path/../deps/qt-5.10.1/darwin/x64/Frameworks',
                        '@excutable_path/../../deps/qt-5.10.1/darwin/x64/Frameworks',
                        '@loader_path/../../deps/qt-5.10.1/darwin/x64/Frameworks'
                    ],
                    'OTHER_CPLUSPLUSFLAGS': [
                        '-stdlib=libc++',
                        '-std=c++11',
                        '-mmacosx-version-min=10.7',
                        '-Wno-inconsistent-missing-override',
                        '-Woverloaded-virtual',
                        '<!@(tools/mac.sh --cflags)'
                    ],
                    'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                },
                'include_dirs': [
                    "<!(node -e \"require('nan')\")",
                    '<!@(tools/mac.sh --include-dirs QtTest QtGui QtCore QtQuick QtQml QtMultimedia QtWidgets QtQuickControls2)'
                ],
                'libraries': [
                    '-undefined dynamic_lookup',
                    '<!@(tools/mac.sh --libs QtGui QtCore QtQuick QtQml QtMultimedia QtWidgets QtQuickControls2 QtTest)'
                ]
            }],
            [
                'OS=="linux"', {
                    'include_dirs': [
                        "<!(node -e \"require('nan')\")",
                    ],
                    'cflags': [
                        '<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets Qt5Quick Qt5Qml)'
                    ],
                    'ldflags': [
                        '<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets Qt5Quick Qt5Qml)'
                    ],
                    'libraries': [
                        '<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets Qt5Quick Qt5Qml)'
                    ]
                }
            ],
            [
                'OS=="win"',
                {
                    'include_dirs': [
                        "<!(node -e \"require('nan')\")",
                        'deps/qt-5.10.1/win32/ia32/include',
                        'deps/qt-5.10.1/win32/ia32/include/QtCore',
                        'deps/qt-5.10.1/win32/ia32/include/QtGui',
                        'deps/qt-5.10.1/win32/ia32/include/QtTest',
                    ],
                    'libraries': [
                        # TODO: fix node-gyp behavior that requires ../
                        '../deps/qt-5.10.1/win32/ia32/lib/QtCore4.lib',
                        '../deps/qt-5.10.1/win32/ia32/lib/QtGui4.lib',
                        '../deps/qt-5.10.1/win32/ia32/lib/QtTest4.lib'
                    ]
                }
            ]
        ]
    }]
}
