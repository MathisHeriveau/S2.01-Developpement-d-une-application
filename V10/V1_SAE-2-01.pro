QT       +=core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += chifoumi.cpp \
    database.cpp \
    dialogconnexion.cpp \
    dialoginscription.cpp \
    dialogparametre.cpp \
    dialogresultat.cpp
SOURCES += main.cpp
SOURCES += modele.cpp
SOURCES += presentation.cpp

HEADERS += chifoumi.h \
    database.h \
    dialogconnexion.h \
    dialoginscription.h \
    dialogparametre.h \
    dialogresultat.h \
    modele.h \
    presentation.h

FORMS += \
    chifoumi.ui \
    dialogconnexion.ui \
    dialoginscription.ui \
    dialogparametre.ui \
    dialogresultat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressourcesChifoumi.qrc \
    ressourcesChifoumi.qrc
