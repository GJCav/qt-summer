#include "TextBoxItem.h"
#include <QtWidgets>

TextBoxItem::TextBoxItem(QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    this->setZValue(4000);

    mProxy = new QGraphicsProxyWidget(this);
    mProxy->setParent(this);

    mTextItem = new QGraphicsTextItem(mProxy);
    mTextItem->setPos(Margin, Margin);

    mPanel = new LightWoodPanel();
    mProxy->setWidget(mPanel);

    auto f = mTextItem->font();
    f.setFamily("Microsoft YaHei");
    mTextItem->setFont(f);

    setSize(100, 60);
    this->setHandlesChildEvents(true);
}

const QRect &TextBoxItem::size() const
{
    return mBdnRect;
}

void TextBoxItem::setSize(const int w, const int h)
{
    mBdnRect = QRect(0, 0, qMax(w, Margin*2+20), qMax(h, Margin*2+20));
    //mTextItem->setTextWidth(qMax(w, Margin*2+20) - Margin*2); // 让使用者确定是不是要换行
    prepareGeometryChange();
}

void TextBoxItem::setEnableShadow(bool v)
{
    if(v){
        QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
        e->setBlurRadius(20);
        e->setOffset(10, 10);
        e->setColor(QColor(0, 0, 0, 128));
        this->setGraphicsEffect(e);
    }else{
        this->setGraphicsEffect(nullptr);
    }
}

void TextBoxItem::show()
{
    setVisible(true);
    if(mUseAnimation){
        mAni->setDirection(mAni->Forward);
        mAni->start();
    }
}

bool TextBoxItem::useAnimation() const
{
    return mUseAnimation;
}

void TextBoxItem::setUseAnimation(bool newUseAnimation)
{
    mUseAnimation = newUseAnimation;
    if(mUseAnimation){
        auto floatAni = new QPropertyAnimation(this);
        floatAni->setTargetObject(this);
        floatAni->setPropertyName("y");
        floatAni->setDuration(600);
        floatAni->setStartValue(y() - 20);
        floatAni->setEndValue(y());
        floatAni->setEasingCurve(QEasingCurve::InOutQuad);

        auto opacityAni = new QPropertyAnimation(this);
        opacityAni->setTargetObject(this);
        opacityAni->setPropertyName("opacity");
        opacityAni->setDuration(600);
        opacityAni->setStartValue(0);
        opacityAni->setEndValue(1);
        opacityAni->setEasingCurve(QEasingCurve::InOutQuad);

        mAni = new QParallelAnimationGroup(this);
        mAni->addAnimation(floatAni);
        mAni->addAnimation(opacityAni);
    }

}

void TextBoxItem::close()
{
    //this->setVisible(false);
    if(mUseAnimation){
        mAni->setDirection(mAni->Backward);
        mAni->start();
        connect(mAni, &QParallelAnimationGroup::finished, this, [this](){
            this->setVisible(false);
        });
    }
}


QRectF TextBoxItem::boundingRect() const
{
    return mBdnRect;
}

void TextBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TextBoxItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void TextBoxItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}
