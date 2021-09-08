QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    R.cpp \
    item/CellIndicatorItem.cpp \
    item/GameCharItem.cpp \
    item/LevelCellItem.cpp \
    item/MeowKnightItem.cpp \
    item/PopupTextItem.cpp \
    item/PropItem.cpp \
    item/SelectIndicatorItem.cpp \
    item/hud/ButtonItem.cpp \
    item/hud/IconItem.cpp \
    model/EnemyAI.cpp \
    model/GameCharAction.cpp \
    model/GameCharacter.cpp \
    model/GameProp.cpp \
    model/GameScene.cpp \
    model/HUD.cpp \
    model/Level.cpp \
    main.cpp \
    model/action/AttackAct.cpp \
    model/action/HealAct.cpp \
    model/action/MoveAct.cpp \
    model/ai/BaseAI.cpp \
    model/special/AthleteMeow.cpp \
    model/special/BossMeow.cpp \
    model/special/DoctorMeow.cpp \
    model/special/OrangeMeow.cpp \
    test/TestWindow.cpp \
    ui/DarkPanel.cpp \
    ui/HUDDesign.cpp \
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
    item/CellIndicatorItem.h \
    item/GameCharItem.h \
    item/LevelCellItem.h \
    item/MeowKnightItem.h \
    item/PopupTextItem.h \
    item/PropItem.h \
    item/SelectIndicatorItem.h \
    item/hud/ButtonItem.h \
    item/hud/IconItem.h \
    model/EnemyAI.h \
    model/GameCharAction.h \
    model/GameCharacter.h \
    model/GameProp.h \
    model/GameScene.h \
    model/HUD.h \
    model/Level.h \
    model/action/AttackAct.h \
    model/action/HealAct.h \
    model/action/MoveAct.h \
    model/ai/BaseAI.h \
    model/special/AthleteMeow.h \
    model/special/BossMeow.h \
    model/special/DoctorMeow.h \
    model/special/OrangeMeow.h \
    test/TestWindow.h \
    ui/DarkPanel.h \
    ui/HUDDesign.h \
    ui/LightDarkPanel.h \
    ui/LightWoodPanel.h \
    ui/TexturePanel.h \
    util/AsepriteObject.h \
    util/QPixmapAutoSplitter.h \
    util/QPixmapFileSeq.h \
    util/QPixmapGirdSplitter.h \
    util/QPixmapProvider.h

FORMS += \
    test/TestWindow.ui \
    ui/HUDDesign.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    asset.qrc

DISTFILES += \
    asset/icon/Transparent Icons & Drop Shadow.png
