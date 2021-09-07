#include "DoctorMeow.h"

DoctorMeow::DoctorMeow(GameCharItem *item, GameScene *game, int role)
    : GameCharacter(item, game, role)
{
    setName("庸医喵");
    mHealAct = new HealAct(this, this);
}


QVector<GameCharAction *> DoctorMeow::requestActionMenu()
{
    auto v = GameCharacter::requestActionMenu();
    v.append(mHealAct);
    return v;
}


void DoctorMeow::endTurn()
{
    GameCharacter::endTurn();
    mHealAct->reset();
}
