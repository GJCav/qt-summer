#include "R.h"

namespace {
QGraphicsScene *defaultScene;
QGraphicsView *defaultView;

}

namespace R{

const QPixmap *GUIPixmap;
const QPixmap *BtnPixmap;
const QPixmap *IconPixmap;

namespace Level{
const QPixmap *PlantPixmap;
const QPixmap *PlantShadowPixmap;
const QPixmap *PropsPixmap;
const QPixmap *PropsShadowPixmap;
const QPixmap *StructPixmap;
const QPixmap *GrassPixmap;
const QPixmap *StoneGroundPixmap;
const QPixmap *WallPixmap;
QPixmapGirdSplitter *GrassTextureProvider;
const QPixmap *GrassTexture;
QPixmapGirdSplitter *GrassWithStoneTextureProvider;
//QPixmapGirdSplitter *WallTextureProvider;

void initLevelResource(){
    PlantPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Plant.png");
    PlantShadowPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Shadow Plant.png");
    PropsPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Props.png");
    PropsShadowPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Shadow.png");
    StructPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Struct.png");
    GrassPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Tileset Grass.png");
    StoneGroundPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Tileset Stone Ground.png");
    WallPixmap = new QPixmap(":/asset/Pixel Art Top Down/TX Tileset Wall.png");

    GrassTextureProvider = new QPixmapGirdSplitter();
    GrassTextureProvider->setPixmap(GrassPixmap->copy(0, 0, 8*16, 8*16));
    GrassTextureProvider->setWidth(16);
    GrassTextureProvider->setHeight(16);

    GrassTexture = new QPixmap(GrassPixmap->copy(0, 0, 8*16, 8*16));
    GrassWithStoneTextureProvider = new QPixmapGirdSplitter();
    GrassWithStoneTextureProvider->setPixmap(GrassPixmap->copy(0, 128, 8*16, 8*16));
    GrassWithStoneTextureProvider->setWidth(16);
    GrassWithStoneTextureProvider->setHeight(16);

//    WallTextureProvider = new QPixmapGirdSplitter();
//    WallTextureProvider->setPixmap(*WallPixmap);
//    WallTextureProvider->setWidth(16);
//    WallTextureProvider->setHeight(16);
}
}

void initResource()
{
    defaultScene = new QGraphicsScene();
    defaultView = new QGraphicsView();

    defaultView->setScene(defaultScene);
    defaultView->setSceneRect(0, 0, 800, 600);

    GUIPixmap = new QPixmap(":/asset/ui/GUI.png");
    BtnPixmap = new QPixmap(":/asset/ui/Button.png");
    IconPixmap = new QPixmap(":/asset/icon/Transparent Icons.png");

    Level::initLevelResource();
}

QGraphicsView *gameView()
{
    return defaultView;
}

QGraphicsScene *gameScene()
{
    return defaultScene;
}
}



