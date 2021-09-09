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
    GrassWithStoneTextureProvider->setPixmap(GrassPixmap->copy(0, 176, 4*16, 4*16));
    GrassWithStoneTextureProvider->setWidth(16);
    GrassWithStoneTextureProvider->setHeight(16);

//    WallTextureProvider = new QPixmapGirdSplitter();
//    WallTextureProvider->setPixmap(*WallPixmap);
//    WallTextureProvider->setWidth(16);
//    WallTextureProvider->setHeight(16);
}
}

namespace Sound{
static QAudioOutput DefaultAudioOutput;
QMediaPlayer BkgMusic;
QSoundEffect Clicked;
QSoundEffect Enemy;
QSoundEffect Friend;
QSoundEffect Sword;
QSoundEffect TakeDamage;
QSoundEffect Healed;
QSoundEffect Success;
QSoundEffect Fail;
QSoundEffect ToggleHUD;

void initSound(){
    BkgMusic.setAudioOutput(&DefaultAudioOutput);
    BkgMusic.setSource(QUrl("qrc:/asset/sound/background.m4a"));
    QObject::connect(&BkgMusic, &QMediaPlayer::mediaStatusChanged, &BkgMusic, [](QMediaPlayer::MediaStatus s){
        if(s == QMediaPlayer::EndOfMedia){
            BkgMusic.play();
        }
    });

    Clicked.setSource(QUrl("qrc:/asset/sound/click.wav"));
    Enemy.setSource(QUrl("qrc:/asset/sound/enemy.wav"));
    Friend.setSource(QUrl("qrc:/asset/sound/friend.wav"));
    Sword.setSource(QUrl("qrc:/asset/sound/Sword.wav"));
    TakeDamage.setSource(QUrl("qrc:/asset/sound/gethurt.wav"));
    Healed.setSource(QUrl("qrc:/asset/sound/healed.wav"));
    Success.setSource(QUrl("qrc:/asset/sound/success.wav"));
    Fail.setSource(QUrl("qrc:/asset/sound/fail.wav"));
    ToggleHUD.setSource(QUrl("qrc:/asset/sound/openhud.wav"));
}
}

void initResource()
{

    GUIPixmap = new QPixmap(":/asset/ui/GUI.png");
    BtnPixmap = new QPixmap(":/asset/ui/Button.png");
    IconPixmap = new QPixmap(":/asset/icon/Transparent Icons.png");

    Level::initLevelResource();
    Sound::initSound();
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



