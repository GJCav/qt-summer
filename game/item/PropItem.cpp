#include "PropItem.h"
#include "R.h"

#include <QtGui>

using PropType = PropItem::PropType;

PropItem::PropItem(int type, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    setZValue(ZValue);
    setPropType(type);

    setFlag(ItemSendsGeometryChanges);

    // debug only
    //setFlag(QGraphicsItem::ItemIsMovable);

    connect(this, &PropItem::yChanged, this, &PropItem::updateZValue);

}

int PropItem::propType() const
{
    return mPropType;
}

void PropItem::setPropType(int newPropType)
{
    if(newPropType == mPropType) return;
    mPropType = newPropType;
    if(mPropType == PropType::None) return;

    switch(mPropType){
    case PropType::Chest:
        mPropTexture = R::Level::PropsPixmap->copy(96, 29, 37, 32);
        mShadowTextrue = R::Level::PropsShadowPixmap->copy(96, 29, 37, 32);
        mBoundingRect = {0, -32, 37, 32};
        this->setScale(2);
        break;
    case PropType::Magic:
        mPropTexture = R::Level::PropsPixmap->copy(227, 9, 32, 52);
        mShadowTextrue = R::Level::PropsShadowPixmap->copy(227, 9, 32, 52);
        mBoundingRect = {0, -52, 32, 52};
        this->setScale(2);
        break;
    default:
        Q_ASSERT_X(false, "setPropType", "unsupport prop type");
    }
    prepareGeometryChange();
    update();
}

void PropItem::updateZValue()
{
    setZValue(ZValue+pos().y());
}

const QPixmap &PropItem::propTexture() const
{
    return mPropTexture;
}

const QPixmap &PropItem::shadowTextrue() const
{
    return mShadowTextrue;
}

QVariant PropItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene()){
        //QPoint newPos = value.toPoint();
        //setZValue(ZValue+newPos.y());
    }
    return QGraphicsItem::itemChange(change, value);
}


QRectF PropItem::boundingRect() const
{
    return mBoundingRect;
}

void PropItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    auto sha = shadowTextrue();
    painter->drawPixmap(
        boundingRect(),
        sha,
        sha.rect()
    );

    auto txt = propTexture();
    painter->drawPixmap(
        boundingRect(),
        txt,
        txt.rect()
    );
}


void PropItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void PropItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
}
