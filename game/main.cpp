
#include "R.h"
#include "model/scene/HelloScene.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

    //R::Sound::BkgMusic->play();


    GameScene *game = new HelloScene();
    game->init();

    QGraphicsView view;
    view.setScene(game);
    view.setSceneRect({0, 0, 1024, 768});
    view.setFixedSize(1024, 768);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();


    return a.exec();
}



















