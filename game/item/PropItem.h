#ifndef PROPITEM_H
#define PROPITEM_H

#include <QGraphicsItem>
#include <QPoint>

class PropItem : public QGraphicsObject
{
    Q_OBJECT

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

signals:
    void clicked(PropItem* src);

private:
    QPixmap mPropTexture;
    QPixmap mShadowTextrue;
    QRect mBoundingRect;
    int mPropType;

private slots:
    void updateZValue();

    // QGraphicsItem interface
public:

    const QPixmap &propTexture() const;
    const QPixmap &shadowTextrue() const;


    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PROPITEM_H
