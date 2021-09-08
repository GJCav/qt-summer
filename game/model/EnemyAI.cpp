#include "EnemyAI.h"
#include "GameScene.h"
#include "GameCharacter.h"
#include "special/DoctorMeow.h"
#include <QtConcurrent/QtConcurrent>

EnemyAI::EnemyAI(GameScene *game)
    : QObject(game), mGame(game)
{
}

void EnemyAI::start()
{
    const auto list = makeStrategy();
    if(list.isEmpty()) {
        emit AITurnFinished();
        return;
    }

    auto future = QtConcurrent::run(list[0]);
    for(int i = 1;i < list.size();i++){
        future.then(list[i]);
    }
    future.then([this](){
        emit AITurnFinished();
    });
}


EnemyAI::Action EnemyAI::moveAction(GameCharacter *ch, QPoint to)
{
    return [=](){
        ch->moveTo(to);
        QThread::msleep(1000);
    };
}

EnemyAI::Action EnemyAI::attackAction(GameCharacter *src, GameCharacter *dst)
{
    return [=](){
        QtConcurrent::run([=](){src->attack();});
        QThread::sleep(200);
        dst->attacked(src->attackPower());
        QThread::msleep(500);
    };
}

EnemyAI::Action EnemyAI::healAction(GameCharacter *src, GameCharacter *dst)
{
    return [=](){
        auto doctor = dynamic_cast<DoctorMeow*>(src);
        if(doctor != nullptr){
            doctor->heal(dst);
            QThread::msleep(500);
        }
    };
}


