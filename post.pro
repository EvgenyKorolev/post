#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T10:03:49
#
#-------------------------------------------------

QT       += core gui sql widgets printsupport
CONFIG   += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = post
TEMPLATE = app
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc
DESTDIR = out

SOURCES += \
    src/browser_letter_in.cpp \
    src/browser_letter_out.cpp \
    src/doc_image.cpp \
    src/editor_letter_in.cpp \
    src/editor_letter_out.cpp \
    src/filtr.cpp \
    src/images_browser.cpp \
    src/images_editors.cpp \
    src/items_fabrica.cpp \
    src/letter.cpp \
    src/letter_in.cpp \
    src/letter_out.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/my_model_in.cpp \
    src/my_model_out.cpp \
    src/my_view.cpp \
    src/proxy_in.cpp \
    src/proxy_out.cpp \
    src/settings.cpp \
    src/functions.cpp \
    src/yes_no.cpp

HEADERS  += \
    src/browser_letter_in.h \
    src/browser_letter_out.h \
    src/doc_image.h \
    src/editor_letter_in.h \
    src/editor_letter_out.h \
    src/filtr.h \
    src/images_browser.h \
    src/images_editors.h \
    src/items_fabrica.h \
    src/letter.h \
    src/letter_in.h \
    src/letter_out.h \
    src/mainwindow.h \
    src/my_model_in.h \
    src/my_model_out.h \
    src/my_view.h \
    src/proxy_in.h \
    src/proxy_out.h \
    src/settings.h \
    src/declaration.h \
    src/functions.h \
    src/yes_no.h

RESOURCES += \
    res.qrc

win32:{
    RC_ICONS = $$PWD/images/k.ico
    VERSION = 0.9.9
    QMAKE_TARGET_PRODUCT = document registration
    QMAKE_TARGET_DESCRIPTION = The program is designed to register incoming and outgoing documents in the workplace Secretary of a small company
    QMAKE_TARGET_COPYRIGHT = Evgeny Korolev E-mail: root@kyrych.ru
}
