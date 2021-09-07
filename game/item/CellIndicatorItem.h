#ifndef CELLINDICATORITEM_H
#define CELLINDICATORITEM_H

#include "LevelCellItem.h"
#include <QGraphicsObject>
#include <QObject>

class CellIndicatorItem : public QGraphicsObject
{
    Q_OBJECT
public:
    constexpr static int CellSize = LevelCellItem::CellSize;

    CellIndicatorItem(QPoint gamePos, QGraphicsItem* parent = nullptr);

    QPoint gamePos() const;
    void setGamePos(QPoint newGamePos);

    const QColor &color() const;
    void setColor(const QColor &newColor);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void clicked(CellIndicatorItem* src);

private:
    QPoint mGamePos;
    QColor mColor;
    bool mMouseHover = false;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CELLINDICATORITEM_H
