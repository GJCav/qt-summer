#include "GameCharItem.h"

GameCharItem::GameCharItem(QGraphicsObject* parent) : QGraphicsObject(parent) {

}



QVariant GameCharItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemSelectedHasChanged && scene()){
        emit selectedChange(value.toBool());
    }
    return QGraphicsObject::itemChange(change, value);
}
