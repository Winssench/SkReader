!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

QT += 3dcore 3drender 3dinput 3dextras widgets

SOURCES += \
    joint.cpp \
    main.cpp \
    mytimer.cpp \
    orbittransformcontroller.cpp \
    skeleton.cpp \
    skeletonbuilder.cpp \
    skeletonview.cpp

HEADERS += \
    joint.h \
    mytimer.h \
    orbittransformcontroller.h \
    skeleton.h \
    skeletonbuilder.h \
    skeletonview.h

DISTFILES += \
    skeleton.csv
