#include "PopupPixmapItem.h"
#include <QtWidgets>
#include <QtGui>

PopupPixmapItem::PopupPixmapItem(const QPixmap& pix, QGraphicsItem*parent)
    : QGraphicsObject(parent)
{
    setPixmap(pix);
}

const QPixmap &PopupPixmapItem::pixmap() const
{
    return mPixmap;
}

void PopupPixmapItem::setPixmap(const QPixmap &newPixmap)
{
    mPixmap = newPixmap;
    prepareGeometryChange();
}

void PopupPixmapItem::popup()
{

    mAniGroup = new QParallelAnimationGroup(this);

    auto floatUp = new QPropertyAnimation();
    floatUp->setTargetObject(this);
    floatUp->setPropertyName("y");
    floatUp->setStartValue(y());
    floatUp->setEndValue(y()-FloatUpDistance);
    floatUp->setDuration(AnimationDuration);
    floatUp->setEasingCurve(QEasingCurve::InCubic);

    auto fadeOut = new QPropertyAnimation();
    fadeOut->setTargetObject(this);
    fadeOut->setPropertyName("opacity");
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->setDuration(AnimationDuration);
    fadeOut->setEasingCurve(QEasingCurve::InCubic);

    mAniGroup->addAnimation(floatUp);
    mAniGroup->addAnimation(fadeOut);

    connect(mAniGroup, &QParallelAnimationGroup::finished, this, [this](){
        this->deleteLater();
    });

    mAniGroup->start();
}


QRectF PopupPixmapItem::boundingRect() const
{
    return mPixmap.rect();
}

void PopupPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, mPixmap);
}
