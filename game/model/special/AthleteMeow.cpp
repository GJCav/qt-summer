#include "AthleteMeow.h"
#include "model/action/MoveAct.h"

AthleteMeow::AthleteMeow(GameCharItem *item, GameScene *game, int role)
    : GameCharacter(item, game, role)
{
    setName("运动喵");
    setHealth(20);
    setDefensivePower(0);
    setAttackPower(10);
    setSpeed(8);
    setLucky(20);
    mMoveAct->setSpeedMin(4);
}


qreal AthleteMeow::speed() const
{
    const qreal sp = GameCharacter::speed();
    qreal r = sp / mSpeed;
    mMoveAct->setSpeedMin(4*r);
    return sp;
}
