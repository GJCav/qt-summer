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
    virtual void setPixmap(const QPixmap &newPixmap);

    inline void recalculate() {
        mSubPixmapRects.clear();
        calculateRects();
    }

    // remember to release the scene of this viewport.
    virtual QGraphicsView *preview(QWidget* parent = nullptr);

protected:
    QPixmap mPixmap;
    QVector<QRect> mSubPixmapRects;

    // override this function.
    virtual void calculateRects() = 0;
};

#endif // QPIXMAPPROVIDER_H
