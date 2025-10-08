QT += core sql network  # Добавьте core, если отсутствует
CONFIG += c++11
SOURCES += \
    main.cpp \
    database.cpp \
    tcpserver.cpp \
    functionsforserver.cpp \
    des.cpp \
    sha384.cpp \
    chordmethod.cpp \
    steganography.cpp
HEADERS += \
    database.h \
    tcpserver.h \
    functionsforserver.h \
    des.h \
    sha384.h \
    chordmethod.h \
    steganography.h
