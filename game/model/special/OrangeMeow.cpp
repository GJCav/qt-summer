#include "OrangeMeow.h"


OrangeMeow::OrangeMeow(GameCharItem *item, GameScene *game, int role)
    : GameCharacter(item, game, role)
{
    setName("橘喵");
    setHealth(50);
    setDefensivePower(5);
    setAttackPower(2);
    setSpeed(2);
}