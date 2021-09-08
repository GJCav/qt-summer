#include "BaseAI.h"

BaseAI::BaseAI(GameScene *game)
    : EnemyAI(game)
{

}


QVector<EnemyAI::function<void ()> > BaseAI::makeStrategy()
{
    QVector<function<void()>> rst;

    return {};
}
