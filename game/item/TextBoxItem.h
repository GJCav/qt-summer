#ifndef TEXTBOXITEM_H
#define TEXTBOXITEM_H

#include "ui/LightWoodPanel.h"
#include <QGraphicsObject>
#include <QGraphicsTextItem>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QFont>

class TextBoxItem : public QGraphicsObject
{
    Q_OBJECT
public:
    constexpr static int Margin = 10;

    TextBoxItem(QGraphicsItem* parent = nullptr);

    inline void setHtml(const QString& text){ mTextItem->setHtml(text); }
    inline void setColor(const QColor c){ mTextItem->setDefaultTextColor(c); }
    inline void setFontPointSize(const int sz) {
        auto f = mTextItem->font();
        f.setPointSize(sz);
        mTextItem->setFont(f);
    }

    int autoCloseTime() const;
    void setAutoCloseTime(int newAutoCloseTime);
    const QRect &size() const;
    void setSize(const int w, const int h);

    void setEnableShadow(bool v);


private:
    int mAutoCloseTime = -1;
    QGraphicsTextItem *mTextItem;
    QRect mBdnRect;

    QGraphicsProxyWidget *mProxy;
    LightWoodPanel* mPanel;


signals:
    void clicked();

public slots:
    void close();
    void show();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TEXTBOXITEM_H
