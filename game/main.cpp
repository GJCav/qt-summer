
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

//    GameScene *game = new HelloScene();
//    game->init();

//    QGraphicsView view;
//    view.setScene(game);
//    view.setSceneRect({0, 0, 1024, 768});
//    view.show();

//    view.setFixedSize(view.size());
//    view.show();

//    QMediaPlayer player;
//    QAudioOutput audioOutput; // chooses the default audio routing
//    player.setAudioOutput(&audioOutput);
//    player.setSource(QUrl("qrc:/asset/sound/background.m4a"));
//    player.play();

//    //player.setPosition(player.duration() / 2);

//    QObject::connect(&player, &QMediaPlayer::durationChanged, [&player](qint64 v){
//        qDebug()<<v;
//        //player.setPosition(player.duration() / 2);
//    });

//    QObject::connect(&player, &QMediaPlayer::positionChanged, [&player](qint64 v){
//        qDebug()<< "posi " <<v;
//        //player.setPosition(player.duration() / 2);
//    });


//    QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, [&player](QMediaPlayer::MediaStatus v){
//        qDebug()<< "state " <<v;
//        if(v == QMediaPlayer::MediaStatus::EndOfMedia);
//        player.play();
//        //player.setPosition(player.duration() / 2);
//    });

    QSoundEffect effect;
    effect.setSource(QUrl("qrc:/asset/sound/click.wav"));
    effect.setLoopCount(QSoundEffect::Infinite);
    effect.setVolume(0.25f);
    effect.play();


    return a.exec();
}



















