#ifndef SELECTINDICATORITEM_H
#define SELECTINDICATORITEM_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class SelectIndicatorItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal upFloatFator MEMBER mUpFloatFactor)

public:
    constexpr static int UpFloatDistance = 6;
    constexpr static int LoopDuration = 800;

public:
    SelectIndicatorItem(QGraphicsObject *parent = nullptr);


private:
    QPixmap mTexture;
    QRect mBdnRect;
    QPropertyAnimation *mFloatAni;
    QPropertyAnimation *mOpacityAni;
    QParallelAnimationGroup *mAniGroup;
    qreal mUpFloatFactor = 0;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SELECTINDICATORITEM_H
