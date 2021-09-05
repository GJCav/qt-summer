QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    R.cpp \
    item/LevelCellItem.cpp \
    item/MeowKnightItem.cpp \
    item/PropItem.cpp \
    model/Level.cpp \
    main.cpp \
    test/TestWindow.cpp \
    ui/DarkPanel.cpp \
    ui/LightDarkPanel.cpp \
    ui/LightWoodPanel.cpp \
    ui/TexturePanel.cpp \
    util/AsepriteObject.cpp \
    util/QPixmapAutoSplitter.cpp \
    util/QPixmapFileSeq.cpp \
    util/QPixmapGirdSplitter.cpp \
    util/QPixmapProvider.cpp

HEADERS += \
    R.h \
    item/LevelCellItem.h \
    item/MeowKnightItem.h \
    item/PropItem.h \
    model/Level.h \
    test/TestWindow.h \
    ui/DarkPanel.h \
    ui/LightDarkPanel.h \
    ui/LightWoodPanel.h \
    ui/TexturePanel.h \
    util/AsepriteObject.h \
    util/QPixmapAutoSplitter.h \
    util/QPixmapFileSeq.h \
    util/QPixmapGirdSplitter.h \
    util/QPixmapProvider.h

FORMS += \
    test/TestWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    asset.qrc
