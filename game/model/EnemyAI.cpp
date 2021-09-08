#include "EnemyAI.h"
#include "GameScene.h"

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
