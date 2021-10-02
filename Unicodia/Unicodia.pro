QT += core gui widgets
CONFIG += c++2a

win32-g++ {
    # To simplify debugging, we statically link these libraries
    QMAKE_CXXFLAGS_DEBUG += -static-libgcc -static-libstdc++
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

debug {
    DEFINES += AT_RANGE_CHECK
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Uc/UcAuto.cpp \
    ../Libs/SelfMade/c_TableCache.cpp \
    ../Libs/SelfMade/i_MemStream.cpp \
    ../Libs/SelfMade/i_TempFont.cpp \
    ../Libs/SelfMade/u_Qstrings.cpp \
    ../Libs/SelfMade/u_Strings.cpp \
    FmPopup.cpp \
    MyWiki.cpp \
    Uc/FontMatch.cpp \
    Uc/UcData.cpp \
    Wiki.cpp \
    main.cpp \
    FmMain.cpp

HEADERS += \
    ../Libs/SelfMade/c_TableCache.h \
    ../Libs/SelfMade/i_ByteSwap.h \
    ../Libs/SelfMade/i_MemStream.h \
    ../Libs/SelfMade/i_TempFont.h \
    ../Libs/SelfMade/u_Iterator.h \
    ../Libs/SelfMade/u_Qstrings.h \
    ../Libs/SelfMade/u_Array.h \
    ../Libs/SelfMade/u_Strings.h \
    ../Libs/SelfMade/u_TinyOpt.h \
    ../Libs/SelfMade/u_TypedFlags.h \
    ../Libs/SelfMade/u_Vector.h \
    FmMain.h \
    FmPopup.h \
    MyWiki.h \
    Skin.h \
    Uc/FontDef.h \
    Uc/FontMatch.h \
    Uc/UcAutoCount.h \
    Uc/UcAutoDefines.h \
    Uc/UcData.h \
    Wiki.h

FORMS += \
    FmMain.ui

INCLUDEPATH += \
    ../Libs/SelfMade \
    Uc

TRANSLATIONS += \
    Unicodia_en_001.ts

win32-g++ {
    LIBS += -lgdi32
}

VERSION = 0.1

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Scripts/scripts.qrc
