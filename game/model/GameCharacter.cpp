#include "GameCharacter.h"
#include "item/PopupTextItem.h"
#include <QtGlobal>
#include <QtCore>
#include <QtGui>
#include <QtConcurrent/QtConcurrent>

GameCharacter::GameCharacter(GameCharItem* item, QObject *parent) : QObject(parent)
{
    mCharItem = item;
    mCharItem->setFlag(QGraphicsItem::ItemIsSelectable);
    connect(mCharItem, &GameCharItem::selectedChange, this, &GameCharacter::selected);
}

void GameCharacter::attacked(const qreal power)
{
    if(mHealth <= 0) return;

    bool canDodge = QRandomGenerator::global()->generate() % 100 < mLucky;
    if(canDodge){
        dodge();
        return;
    }

    const qreal hurt = qMax(power - mDefensivePower, (qreal)0);
    mHealth -= hurt;
    mCharItem->takeDamage(hurt);

    if(mHealth <= 0){
        QTimer::singleShot(500, this, &GameCharacter::die);
    }
}

void GameCharacter::healed(const qreal power)
{
    if(mHealth <= 0) return;
    mHealth += power;
    mCharItem->healed(power);
}

void GameCharacter::moveTo(const QPoint newPos)
{
    const QPoint dest = {newPos.x() * 64, newPos.y() * 64};
    mPos = newPos;
    mCharItem->moveTo(dest);
}

void GameCharacter::setPos(const QPoint newPos)
{
    const QPoint dest = {newPos.x() * 64, newPos.y() * 64};
    mCharItem->setTowards(newPos.x() > mPos.x());
    mPos = newPos;
    mCharItem->setPos(dest);
}

void GameCharacter::die()
{
    this->mCharItem->death();
}

void GameCharacter::dodge()
{
    mCharItem->dodge();
}

void GameCharacter::selected(bool slt)
{
}

QVector<CharAction *> GameCharacter::requestActionMenu()
{
    return {};
}

CharAction::CharAction(QObject *parent) : QObject(parent)
{

}
