#include "PopupTextItem.h"
#include <QtGui>

PopupTextItem::PopupTextItem(const QString& str, const QColor color, QGraphicsObject* parent)
    : QGraphicsTextItem(str, parent)
{
    //mText = new QGraphicsTextItem(str, this);
    setDefaultTextColor(color);

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSizeF(4);
    setFont(font);


}

void PopupTextItem::start()
{
    auto floatUp = new QPropertyAnimation();
    floatUp->setTargetObject(this);
    floatUp->setPropertyName("y");
    floatUp->setStartValue(y());
    floatUp->setKeyValueAt(0.2, y());
    floatUp->setEndValue(y()-FloatUpDistance);
    floatUp->setDuration(AnimationDuration);
    floatUp->setEasingCurve(QEasingCurve::InCubic);

    auto fadeOut = new QPropertyAnimation();
    fadeOut->setTargetObject(this);
    fadeOut->setPropertyName("opactiy");
    fadeOut->setStartValue(1);
    fadeOut->setKeyValueAt(0.2, 1);
    fadeOut->setEndValue(0);
    fadeOut->setDuration(AnimationDuration);
    fadeOut->setEasingCurve(QEasingCurve::InCubic);

    mAniGroup = new QParallelAnimationGroup();
    mAniGroup->addAnimation(floatUp);
    mAniGroup->addAnimation(fadeOut);

    connect(mAniGroup, &QParallelAnimationGroup::finished, this, [this](){
        this->deleteLater();
    });

    mAniGroup->start();
}
