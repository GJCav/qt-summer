#include "ButtonItem.h"
#include <QtGui>
#include <QtWidgets>

ButtonItem::ButtonItem(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    mTextShadowItem = new QGraphicsTextItem(this);
    mTextItem = new QGraphicsTextItem(this);

    mTextShadowItem->setDefaultTextColor(Qt::black);
    mTextShadowItem->setOpacity(0.4);

    QTextOption opt = mTextItem->document()->defaultTextOption();
    opt.setAlignment(Qt::AlignHCenter);
    mTextItem->document()->setDefaultTextOption(opt);
    mTextShadowItem->document()->setDefaultTextOption(opt);

    mTextShadowItem->setPos(ShadowDistance, ShadowDistance);


    QFont f;
    f.setFamily("Microsoft YaHei UI");
    mTextItem->setFont(f);
    mTextShadowItem->setFont(f);

//    setMarginLeft(4);
//    setMarginTop(4);

    mHoverAni = new QPropertyAnimation(this);
    mHoverAni->setTargetObject(this);
    mHoverAni->setPropertyName("x");
    mHoverAni->setLoopCount(-1);
    mHoverAni->setDuration(1000);
    //mHoverAni->setEasingCurve(QEasingCurve::InOutQuad);

    setAcceptHoverEvents(true);

}

const QPixmap &ButtonItem::bckPixmap() const
{
    return mBckPixmap;
}

void ButtonItem::setBckPixmap(const QPixmap &newBckImage)
{
    mBckPixmap = newBckImage;
    mBdnRect = mBckPixmap.rect();
    mTextItem->setTextWidth(mBdnRect.width());
    mTextShadowItem->setTextWidth(mBdnRect.width());
    vAlignText();
}

//int ButtonItem::marginLeft() const
//{
//    return mMarginLeft;
//}

//void ButtonItem::setMarginLeft(int newMarginLeft)
//{
//    mMarginLeft = newMarginLeft;
//    mTextItem->setX(mMarginLeft);
//    mTextShadowItem->setX(mMarginLeft+ShadowDistance);
//}

//int ButtonItem::marginTop() const
//{
//    return mMarginTop;
//}

//void ButtonItem::setMarginTop(int newMarginTop)
//{
//    mMarginTop = newMarginTop;
//    mTextItem->setY(mMarginTop);
//    mTextShadowItem->setY(mMarginTop+ShadowDistance);
//}

int ButtonItem::aniDistance() const
{
    return mAniDistance;
}

void ButtonItem::setAniDistance(int newAniDistance)
{
    mAniDistance = newAniDistance;
}

void ButtonItem::vAlignText()
{
    auto f = mTextItem->font();
    auto m = QFontMetrics(f);
    mTextItem->setY((mBdnRect.height()-m.height())/2-ShadowDistance);
    mTextShadowItem->setY(mTextItem->y()+ShadowDistance);
    mTextShadowItem->setX(mTextItem->x()+ShadowDistance);
}


QRectF ButtonItem::boundingRect() const
{
    return mBdnRect;
}

void ButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0, 0, mBckPixmap);
}


QVariant ButtonItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsObject::itemChange(change, value);
}


void ButtonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mOrgPos = pos();
    mHoverAni->setStartValue(mOrgPos.x());
    mHoverAni->setKeyValueAt(0.25, mOrgPos.x()-mAniDistance);
    mHoverAni->setKeyValueAt( 0.5, mOrgPos.x());
    mHoverAni->setKeyValueAt(0.75, mOrgPos.x()+mAniDistance);
    mHoverAni->setKeyValueAt(   1, mOrgPos.x());
    mHoverAni->start();
    QGraphicsObject::hoverEnterEvent(event);
}

void ButtonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mHoverAni->stop();
    setPos(mOrgPos);
    QGraphicsObject::hoverLeaveEvent(event);
}

void ButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    QGraphicsObject::mouseReleaseEvent(event);
}


void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    event->accept();
}
