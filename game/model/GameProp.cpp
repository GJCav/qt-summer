#include "GameProp.h"

GameProp::GameProp(PropItem *item,  GameScene *game, int type)
    : QObject(game), mGame(game), mPropItem(item)
{
    mPropType = type;
    mPropItem->setParent(this);
    connect(item, &PropItem::clicked, this, &GameProp::clickOn);
    setPos({0, 0});
}

QPoint GameProp::pos() const
{
    return mPos;
}

void GameProp::setPos(QPoint newPos)
{
    mPos = newPos;
    mPropItem->setPos(mPos.x()*CellSize, mPos.y()*CellSize);
}

PropItem *GameProp::propItem() const
{
    return mPropItem;
}

void GameProp::clickOn(PropItem *item)
{
    Q_UNUSED(item);
    emit clicked(this);
}
