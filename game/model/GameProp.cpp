#include "GameProp.h"

GameProp::GameProp(GameScene *game, int type)
    : QObject(game), mGame(game)
{
    mPropType = type;

    mPropItem = new PropItem(type);
    mPropItem->setParent(this);
    connect(mPropItem, &PropItem::clicked, this, &GameProp::clickOn);
    setPos({0, 0});
}

QPoint GameProp::pos() const
{
    return mPos;
}

void GameProp::setPos(QPoint newPos)
{
    mPos = newPos;
    mPropItem->setPos(mPos.x()*CellSize, mPos.y()*CellSize + CellSize);
}

PropItem *GameProp::propItem() const
{
    return mPropItem;
}

int GameProp::propType() const
{
    return mPropType;
}

void GameProp::clickOn(PropItem *item)
{
    Q_UNUSED(item);
    emit clicked(this);
}
