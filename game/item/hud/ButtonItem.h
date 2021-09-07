#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include "ui/TexturePanel.h"
#include <QGraphicsObject>
#include <QObject>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>

class ButtonItem : public QGraphicsObject
{
    Q_OBJECT

signals:
    void clicked();

public:
    constexpr static int ShadowDistance = 3;

    ButtonItem(QGraphicsItem *parent = nullptr);

    const QPixmap &bckPixmap() const;
    void setBckPixmap(const QPixmap &newBckImage);

//    int marginLeft() const;
//    void setMarginLeft(int newMarginLeft);
//    int marginTop() const;
//    void setMarginTop(int newMarginTop);

    inline const QString text() const {return mTextItem->toPlainText();}
    inline void setText(const QString txt) {
        mTextItem->setPlainText(txt);
        mTextShadowItem->setPlainText(txt);

        vAlignText();
    }
    inline void setColor(const QColor c) {
        mTextItem->setDefaultTextColor(c);
    }
    inline void setFontPoint(const int p){
        QFont f = mTextItem->font();
        f.setPointSize(p);
        mTextItem->setFont(f);
        mTextShadowItem->setFont(f);

        vAlignText();
    }

    int aniDistance() const;
    void setAniDistance(int newAniDistance);

private:
    QRect mBdnRect;
    QPixmap mBckPixmap;
//    int mMarginLeft = 0;
//    int mMarginTop = 0;

    QGraphicsTextItem *mTextItem;
    QGraphicsTextItem *mTextShadowItem;

    QPropertyAnimation *mHoverAni;
    QPointF mOrgPos;
    int mAniDistance = 5;

    void vAlignText();

private slots:
    void reactEnabledChange();

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BUTTONITEM_H
