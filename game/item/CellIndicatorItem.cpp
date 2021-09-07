#include "CellIndicatorItem.h"

#include <QtGui>
#include <QtWidgets>

CellIndicatorItem::CellIndicatorItem(QPoint gamePos, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    setAcceptHoverEvents(true);
    setGamePos(gamePos);
}

QPoint CellIndicatorItem::gamePos() const
{
    return mGamePos;
}

void CellIndicatorItem::setGamePos(QPoint newGamePos)
{
    mGamePos = newGamePos;
    this->setPos(mGamePos.x() * CellSize, mGamePos.y() * CellSize);
}


QRectF CellIndicatorItem::boundingRect() const
{
    return {0, 0, CellSize, CellSize};
}

void CellIndicatorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    QPen pen;
    QColor pc(mColor.red(), mColor.green(), mColor.blue(), mHightLight ? 128 : 64);
    pen.setWidth(3);
    pen.setCosmetic(true);
    pen.setColor(mColor);
    painter->setPen(mColor);

    QColor bc(mColor.red(), mColor.green(), mColor.blue(), 32);
    painter->setBrush(bc);

    painter->drawRect(0, 0, CellSize, CellSize);

    if(mMouseHover){
        painter->setPen(Qt::NoPen);

        QRadialGradient r(CellSize/2, CellSize/2, CellSize, CellSize/2, CellSize/2);
        r.setColorAt(0, QColor(255, 255, 255, 0));
        r.setColorAt(0.4, QColor(255, 255, 255, 16));
        r.setColorAt(1, QColor(255, 255, 255, 32));

        painter->setBrush(QBrush(r));
        painter->drawRect(0, 0, CellSize, CellSize);
    }

}

bool CellIndicatorItem::hightLight() const
{
    return mHightLight;
}

void CellIndicatorItem::setHightLight(bool newHightLight)
{
    mHightLight = newHightLight;
}

const QColor &CellIndicatorItem::color() const
{
    return mColor;
}

void CellIndicatorItem::setColor(const QColor &newColor)
{
    mColor = newColor;
}

void CellIndicatorItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mMouseHover = true;
    update();
    QGraphicsObject::hoverEnterEvent(event);
}

void CellIndicatorItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mMouseHover= false;
    update();
    QGraphicsObject::hoverLeaveEvent(event);
}

void CellIndicatorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    event->accept();
}

void CellIndicatorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
    //QGraphicsObject::mouseReleaseEvent(event);
}
