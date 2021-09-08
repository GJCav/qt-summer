#include "DoctorMeow.h"
#include "R.h"
#include "item/PopupPixmapItem.h"
#include <QRandomGenerator>

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

void DoctorMeow::heal(GameCharacter *target)
{
    bool isHeal = (QRandomGenerator::global()->generate() % 10) < 7;

    if(isHeal){
        PopupPixmapItem *popIcon = new PopupPixmapItem(
            R::IconPixmap->copy(128, 288, 32, 32),
            charItem()
        );
        popIcon->setPos(2, -8);
        popIcon->popup();
        QTimer::singleShot(200, [target](){target->healed(10);});
    }else{
        PopupPixmapItem *popIcon = new PopupPixmapItem(
            R::IconPixmap->copy(0, 835, 32, 32),
            charItem()
        );
        popIcon->setPos(2, -8);
        popIcon->popup();
        QTimer::singleShot(200, [target](){target->attacked(10);});
    }

}
