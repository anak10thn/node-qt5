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
            # 'src/QtTest/qtesteventlist.cc'
        ],
        'conditions': [
            [
                'OS=="mac"',
                {
                    'include_dirs': [
                        "<!(node -e \"require('nan')\")",
                        'deps/qt-5.10.1/darwin/x64/include',
                        'deps/qt-5.10.1/darwin/x64/include/QtCore',
                        'deps/qt-5.10.1/darwin/x64/include/QtGui',
                        'deps/qt-5.10.1/darwin/x64/include/QtTest'
                    ],
                    'libraries': [
                        # TODO: fix node-gyp behavior that requires ../
                        '-Wl,-rpath,@loader_path/../deps/qt-5.10.1/darwin/x64/lib/QtCore.framework/QtCore',
                        '-Wl,-rpath,@loader_path/../deps/qt-5.10.1/darwin/x64/lib/QtGui.framework/QtGui',
                        '-Wl,-rpath,@loader_path/../deps/qt-5.10.1/darwin/x64/lib/QtTest.framework/QtTest'
                    ],
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS':
                        'YES',
                        'OTHER_CFLAGS': [
                            '-g', '-mmacosx-version-min=10.7', '-std=c++11',
                            '-stdlib=libc++', '-O3',
                            '-D__STDC_CONSTANT_MACROS',
                            '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE',
                            '-Wall'
                        ],
                        'OTHER_CPLUSPLUSFLAGS': [
                            '-g', '-mmacosx-version-min=10.7', '-std=c++11',
                            '-stdlib=libc++', '-O3',
                            '-D__STDC_CONSTANT_MACROS',
                            '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE',
                            '-Wall'
                        ]
                    }
                }
            ],
            [
                'OS=="linux"', {
                    'include_dirs': [
                        "<!(node -e \"require('nan')\")",
                    ],
                    'cflags': [
                        '<!@(pkg-config --cflags Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets)'
                    ],
                    'ldflags': [
                        '<!@(pkg-config --libs-only-L --libs-only-other Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets)'
                    ],
                    'libraries': [
                        '<!@(pkg-config --libs-only-l Qt5Core Qt5Gui Qt5Test Qt5Multimedia Qt5Widgets)'
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
