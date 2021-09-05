#ifndef PROPITEM_H
#define PROPITEM_H

#include <QGraphicsItem>
#include <QPoint>

class PropItem : public QGraphicsItem
{
public:
    constexpr static int ZValue = 200;

    struct PropType{
        constexpr static int None = 0;
        constexpr static int Chest = 100;
        constexpr static int Magic = 200;
    };

    PropItem(int propType = 0, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int propType() const;
    void setPropType(int newPropType);




private:
    QPixmap mPropTexture;
    QPixmap mShadowTextrue;
    QRect mBoundingRect;
    int mPropType;

    // QGraphicsItem interface
public:

    const QPixmap &propTexture() const;
    const QPixmap &shadowTextrue() const;

};

#endif // PROPITEM_H
