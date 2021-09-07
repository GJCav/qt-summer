#include "GameCharItem.h"

GameCharItem::GameCharItem(QGraphicsObject* parent) : QGraphicsObject(parent) {
    connect(this, &GameCharItem::yChanged, this, &GameCharItem::updateZValue);
}



QVariant GameCharItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemSelectedHasChanged && scene()){
        emit selectedChange(value.toBool());
    }
    return QGraphicsObject::itemChange(change, value);
}

void GameCharItem::updateZValue()
{
    setZValue(pos().y()+ZValue);
}
