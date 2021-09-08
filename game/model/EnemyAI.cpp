#include "EnemyAI.h"
#include "GameScene.h"

#include <QtConcurrent/QtConcurrent>

EnemyAI::EnemyAI(GameScene *game)
    : QObject(game), mGame(game)
{
}

void EnemyAI::start()
{

}
