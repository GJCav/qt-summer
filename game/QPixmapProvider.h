#ifndef QPIXMAPPROVIDER_H
#define QPIXMAPPROVIDER_H

#include <QPixmap>
#include <QString>

class QPixmapProvider
{
public:
    QPixmapProvider(QString srcPath);

    QPixmap pixmapAt(int row, int col) const;
    const QRect pixmapRectAt(int row, int col) const;

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
    const QPixmap mPixmap;
    int mOffsetX = 0;
    int mOffsetY = 0;
    int mGapX = 0;
    int mGapY = 0;
    int mWidth = 0;
    int mHeight = 0;
};

#endif // QPIXMAPPROVIDER_H
