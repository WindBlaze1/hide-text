QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caesar.cpp \
    crypgraphy.cpp \
    cryptography.cpp \
    dcrypt.cpp \
    decode.cpp \
    encode.cpp \
    encryption.cpp \
    rsa.cpp \
    rsa_decrypt.cpp \
    rsa_decrypt_final.cpp \
    rsa_encrypt.cpp \
    stegraphy.cpp \
    main.cpp \
    mainwindow.cpp \
    steganography.cpp \
    vigenere.cpp

HEADERS += \
    caesar.h \
    crypgraphy.h \
    cryptography.h \
    dcrypt.h \
    decode.h \
    encode.h \
    encryption.h \
    rsa.h \
    rsa_decrypt.h \
    rsa_decrypt_final.h \
    rsa_encrypt.h \
    stegraphy.h \
    mainwindow.h \
    steganography.h \
    vigenere.h

FORMS += \
    caesar.ui \
    cryptography.ui \
    dcrypt.ui \
    decode.ui \
    encode.ui \
    encryption.ui \
    mainwindow.ui \
    rsa_decrypt.ui \
    rsa_decrypt_final.ui \
    rsa_encrypt.ui \
    steganography.ui \
    vigenere.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    Resources.qrc

RC_ICONS = icon2.ico
#RC_FILE = p1rc.rc
