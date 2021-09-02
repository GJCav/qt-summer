#include "QPixmapGirdSplitter.h"

QPixmapGirdSplitter::QPixmapGirdSplitter()
{
}

QPixmapGirdSplitter::QPixmapGirdSplitter(QString srcPath)
{
    setPixmap(QPixmap(srcPath));
}

int QPixmapGirdSplitter::offsetX() const
{
    return mOffsetX;
}

int QPixmapGirdSplitter::offsetY() const
{
    return mOffsetY;
}

int QPixmapGirdSplitter::gapX() const
{
    return mGapX;
}

int QPixmapGirdSplitter::gapY() const
{
    return mGapY;
}

int QPixmapGirdSplitter::width() const
{
    return mWidth;
}

int QPixmapGirdSplitter::height() const
{
    return mHeight;
}

void QPixmapGirdSplitter::setOffsetX(int newOffsetX)
{
    mOffsetX = newOffsetX;
}

void QPixmapGirdSplitter::setOffsetY(int newOffsetY)
{
    mOffsetY = newOffsetY;
}

void QPixmapGirdSplitter::setGapX(int newGapX)
{
    mGapX = newGapX;
}

void QPixmapGirdSplitter::setGapY(int newGapY)
{
    mGapY = newGapY;
}

void QPixmapGirdSplitter::setWidth(int newWidth)
{
    mWidth = newWidth;
}

void QPixmapGirdSplitter::setHeight(int newHeight)
{
    mHeight = newHeight;
}


void QPixmapGirdSplitter::calculateRects()
{
    if(mWidth == 0 || mHeight == 0)
        return;
    const int imgWidth = mPixmap.width();
    const int imgHeight = mPixmap.height();
    int x = mOffsetX;
    int y = mOffsetY;
    while(y + mHeight < imgHeight){
        mSubPixmapRects.append({x, y, mWidth, mHeight});
        x += mWidth + mGapX;
        if(x + mWidth >= imgWidth){
            x = mOffsetX;
            y += mHeight + mGapY;
        }
    }
}































