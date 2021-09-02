#ifndef QPIXMAPPROVIDER_H
#define QPIXMAPPROVIDER_H

#include <QtCore>
#include <QtWidgets>

class QPixmapProvider
{
public:
    QPixmapProvider();

    inline const QPixmap subPixmapAt(const int index) const { return mPixmap.copy(mSubPixmapRects.at(index)); }

    inline const QPixmap subPixmapAt(const QPoint pos) const {
        foreach(const QRect& rect, mSubPixmapRects){
            if(rect.contains(pos)){
                return mPixmap.copy(rect);
            }
        }
        return QPixmap{};
    }

    inline const QRect subPixmapRectAt(const int index) const { return mSubPixmapRects.at(index); }

    inline const QRect subPixmapRectAt(const QPoint pos) const {
        foreach(const QRect& rect, mSubPixmapRects){
            if(rect.contains(pos)){
                return rect;
            }
        }
        return QRect{};
    }

    inline const QPixmap &pixmap() const { return mPixmap; }

    inline const QVector<QRect> &subPixmapRects() const { return mSubPixmapRects; }

    // this function maybe time consuming.
    // consider using async method here.
    inline virtual void setPixmap(const QPixmap &newPixmap) {
        if((&newPixmap) == (&mPixmap))
            return;

        mPixmap = newPixmap;
        recalculate();
    }

    inline void recalculate() {
        mSubPixmapRects.clear();
        calculateRects();
    }

    // remember to release the scene of this viewport.
    inline QGraphicsView *preview(QWidget* parent = nullptr) {
        QGraphicsView *view = new QGraphicsView(parent);
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addPixmap(mPixmap);
        QPen pen(Qt::red);
        pen.setCosmetic(true);
        QBrush brush(Qt::red);
        for(int i = 0;i < mSubPixmapRects.length();i++){
            scene->addRect(mSubPixmapRects.at(i), pen);
            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i));
            text->setPos(mSubPixmapRects.at(i).topLeft());
            text->setPen(pen);
            text->setBrush(brush);
        }
        view->setScene(scene);
        return view;
    }

protected:
    QPixmap mPixmap;
    QVector<QRect> mSubPixmapRects;

    // override this function.
    virtual void calculateRects() = 0;
};

#endif // QPIXMAPPROVIDER_H
