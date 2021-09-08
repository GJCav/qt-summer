#include "BaseAI.h"

BaseAI::BaseAI(GameScene *game)
    : EnemyAI(game)
{

}


QVector<function<void ()> > BaseAI::makeStrategy()
{
}
