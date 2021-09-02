#ifndef QPIXMAPAUTOSPLITTER_H
#define QPIXMAPAUTOSPLITTER_H

#include "QPixmapProvider.h"
#include <vector>

class QPixmapAutoSplitter : public QPixmapProvider
{
public:
    QPixmapAutoSplitter();
    QPixmapAutoSplitter(QString srcPath);

    inline int splitThreshold() const { return mSplitThreshold; }
    void setSplitThreshold(int newSplitThreshold);

private:
    int mSplitThreshold = 5;
    /**
     * State:
     *  -1: unsearched
     *  other: distance to the nereast colored pixel
     */
    using StateMap = std::vector<std::vector<int>>;
    inline void updateRect(QRect& rect, QPoint pos) const {
        if(pos.x() < rect.left())   rect.setLeft(pos.x());
        if(pos.y() < rect.top())    rect.setTop(pos.y());
        if(pos.x() > rect.right())  rect.setRight(pos.x());
        if(pos.y() > rect.bottom()) rect.setBottom(pos.y());
    }
    inline bool isTransparentColor(const QColor& color) const {
        if(color.alpha() == 0) return true;
        return false;
    }

    QRect floodFillSearch(const QPoint pos, StateMap &state, const QImage& image);

    // QPixmapProvider interface
protected:
    void calculateRects() override;
};

#endif // QPIXMAPAUTOSPLITTER_H
