QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Caja.cpp \
    Escena.cpp \
    Estructura.cpp \
    Obstaculo.cpp \
    controles.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    particula.cpp \
    simulacion.cpp

HEADERS += \
    Caja.h \
    Escena.h \
    Estructura.h \
    Obstaculo.h \
    controles.h \
    juego.h \
    jugador.h \
    particula.h \
    simulacion.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc
