#ifndef R_H
#define R_H

#include "util/QPixmapProvider.h"
#include "util/QPixmapGirdSplitter.h"
#include "util/AsepriteObject.h"
#include <QtCore>
#include <QtWidgets>
#include <QtMultimedia>

namespace R{

extern const QPixmap *GUIPixmap;
extern const QPixmap *BtnPixmap;
extern const QPixmap *IconPixmap;

namespace Level{
extern const QPixmap *PlantPixmap;
extern const QPixmap *PlantShadowPixmap;
extern const QPixmap *PropsPixmap;
extern const QPixmap *PropsShadowPixmap;
extern const QPixmap *StructPixmap;
extern const QPixmap *GrassPixmap;
extern const QPixmap *StoneGroundPixmap;
extern const QPixmap *WallPixmap;
extern QPixmapGirdSplitter *GrassTextureProvider;
extern const QPixmap *GrassTexture;
extern QPixmapGirdSplitter *GrassWithStoneTextureProvider;
//extern QPixmapGirdSplitter *WallTextureProvider;

void initLevelResource();
}

namespace Sound{
extern QMediaPlayer *BkgMusic;
//extern QSoundEffect *Clicked;
//extern QSoundEffect *Enemy;
//extern QSoundEffect *Friend;
//extern QSoundEffect *Sword;
//extern QSoundEffect *TakeDamage;
//extern QSoundEffect *Healed;
//extern QSoundEffect *Success;
//extern QSoundEffect *Fail;
//extern QSoundEffect *ToggleHUD;

void initSound();
}

void initResource();

void ensureSoundEffectIsReady(QVector<const QSoundEffect*> sounds);
}

#endif // R_H
