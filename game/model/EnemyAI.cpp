#include "EnemyAI.h"
#include "GameScene.h"
#include "GameCharacter.h"
#include "special/DoctorMeow.h"
#include <QtConcurrent/QtConcurrent>

EnemyAI::EnemyAI(GameScene *game)
    : QObject(game), mGame(game)
{
}



//EnemyAI::Action EnemyAI::moveAction(GameCharacter *ch, QPoint to)
//{
//    qDebug() << "move " << ch->pos() << " to " << to;
//    return [=](){
//        ch->moveTo(to);
//        //QThread::msleep(1000);
//    };
//}

//EnemyAI::Action EnemyAI::healAction(GameCharacter *src, GameCharacter *dst)
//{
//    return [=](){
//        auto doctor = dynamic_cast<DoctorMeow*>(src);
//        if(doctor != nullptr){
//            doctor->heal(dst);
//            //QThread::msleep(500);
//        }
//    };
//}

GameScene *EnemyAI::game() const
{
    return mGame;
}


