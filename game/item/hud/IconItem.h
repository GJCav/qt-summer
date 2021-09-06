#ifndef ICONITEM_H
#define ICONITEM_H

#include <QGraphicsPixmapItem>

class IconItem : public QObject, public QGraphicsPixmapItem
{
public:
    IconItem(QGraphicsItem* parent = nullptr, QObject* objParent = nullptr);
};

#endif // ICONITEM_H
