#ifndef POPUPPIXMAPITEM_H
#define POPUPPIXMAPITEM_H

#include <QGraphicsObject>
#include <QObject>
#include <QParallelAnimationGroup>

class PopupPixmapItem : public QGraphicsObject
{
    Q_OBJECT
public:
    constexpr static int FloatUpDistance = 5;
    constexpr static int AnimationDuration = 400;
    PopupPixmapItem(const QPixmap& pix, QGraphicsItem *parent);

    const QPixmap &pixmap() const;
    void setPixmap(const QPixmap &newPixmap);

    // play the animation, then delete self
    void popup();

    inline const auto animation() {return mAniGroup;}

private:
    QPixmap mPixmap;
    QParallelAnimationGroup* mAniGroup = nullptr;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // POPUPPIXMAPITEM_H
