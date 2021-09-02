#ifndef QPIXMAPGIRDSPLITTER_H
#define QPIXMAPGIRDSPLITTER_H

#include "QPixmapProvider.h"

#include <QPixmap>
#include <QString>

class QPixmapGirdSplitter : public QPixmapProvider
{
public:
    QPixmapGirdSplitter();
    QPixmapGirdSplitter(QString path);

    int offsetX() const;
    int offsetY() const;
    int gapX() const;
    int gapY() const;
    int width() const;
    int height() const;

    void setOffsetX(int newOffsetX);
    void setOffsetY(int newOffsetY);
    void setGapX(int newGapX);
    void setGapY(int newGapY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);

private:
    int mOffsetX = 0;
    int mOffsetY = 0;
    int mGapX = 0;
    int mGapY = 0;
    int mWidth = 0;
    int mHeight = 0;

    // QPixmapProvider interface
protected:
    void calculateRects() override;
};

#endif // QPIXMAPGIRDSPLITTER_H
