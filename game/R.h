#ifndef R_H
#define R_H

#include "util/QPixmapProvider.h"
#include "util/QPixmapGirdSplitter.h"
#include "util/AsepriteObject.h"
#include <QtCore>
#include <QtWidgets>

namespace R{

extern const QPixmap *GUIPixmap;
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


void initResource();
QGraphicsView* gameView();
QGraphicsScene* gameScene();
}

#endif // R_H
