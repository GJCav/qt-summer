#include "DoctorMeow.h"
#include "R.h"

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


QVector<QPixmap> DoctorMeow::requestIcons()
{
    auto list = GameCharacter::requestIcons();
    list.append(R::IconPixmap->copy(160, 96, 32, 32));
    return list;
}
