
#include "R.h"
#include "model/scene/HelloScene.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

//    GameScene *game = new HelloScene();
//    game->init();

//    QGraphicsView view;
//    view.setScene(game);
//    view.setSceneRect({0, 0, 1024, 768});
//    view.show();

//    view.setFixedSize(view.size());
//    view.show();

    auto player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->setVolume(50);
    player->play();


    return a.exec();
}



















