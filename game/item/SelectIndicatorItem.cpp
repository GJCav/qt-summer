#include "SelectIndicatorItem.h"
#include "R.h"
#include <QtGui>

SelectIndicatorItem::SelectIndicatorItem(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{
    QTransform t;
    t.rotate(-90);
    mTexture = R::GUIPixmap->copy(133, 36, 5, 6).transformed(t);
    mBdnRect = {
        -mTexture.width() / 2,
        -mTexture.height() - UpFloatDistance,
        mTexture.width(),
        mTexture.height() + UpFloatDistance
    };

    mFloatAni = new QPropertyAnimation();
    mFloatAni->setTargetObject(this);
    mFloatAni->setPropertyName("upFloatFator");
    mFloatAni->setStartValue(1);
    mFloatAni->setKeyValueAt(0.5, 0);
    mFloatAni->setEndValue(1);
    mFloatAni->setDuration(LoopDuration);
    mFloatAni->setEasingCurve(QEasingCurve::OutInQuad);

    mOpacityAni = new QPropertyAnimation();
    mOpacityAni->setTargetObject(this);
    mOpacityAni->setPropertyName("opacity");
    mOpacityAni->setStartValue(0);
    mOpacityAni->setKeyValueAt(0.5, 1);
    mOpacityAni->setEndValue(0);
    mOpacityAni->setDuration(LoopDuration);
    mOpacityAni->setEasingCurve(QEasingCurve::OutInQuad);

    mAniGroup = new QParallelAnimationGroup(this);
    mAniGroup->addAnimation(mFloatAni);
    mAniGroup->addAnimation(mOpacityAni);
    mAniGroup->setLoopCount(-1);
    mAniGroup->start();
}

QRectF SelectIndicatorItem::boundingRect() const
{
    return mBdnRect;
}

void SelectIndicatorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const int y = -mTexture.height() - mUpFloatFactor * UpFloatDistance;
    painter->drawPixmap(
        {mBdnRect.left(), y, mTexture.width(), mTexture.height()},
        mTexture,
        mTexture.rect()
    );
}
