#ifndef POPUPTEXTITEM_H
#define POPUPTEXTITEM_H

#include <QGraphicsObject>
#include <QGraphicsTextItem>
#include <QParallelAnimationGroup>

class PopupTextItem : public QGraphicsTextItem
{
public:
    constexpr static int FloatUpDistance = 3;
    constexpr static int AnimationDuration = 400;

    PopupTextItem(const QString& str, const QColor color, QGraphicsObject* parent);
    void start();

    inline const QParallelAnimationGroup* animation() { return mAniGroup;}

private:
    QParallelAnimationGroup* mAniGroup = nullptr;
};

#endif // POPUPTEXTITEM_H
