#include "QPixmapProvider.h"

QPixmapProvider::QPixmapProvider(QString srcPath) :
    mPixmap(srcPath)
{
}

QPixmap QPixmapProvider::pixmapAt(int row, int col) const
{
    return mPixmap.copy(pixmapRectAt(row, col));
}

const QRect QPixmapProvider::pixmapRectAt(int row, int col) const
{
    const int x = mOffsetX + col * mWidth + col * mGapX;
    const int y = mOffsetY + row * mHeight + row * mGapY;
    return {x, y, mWidth, mHeight};
}


int QPixmapProvider::offsetX() const
{
    return mOffsetX;
}

int QPixmapProvider::offsetY() const
{
    return mOffsetY;
}

int QPixmapProvider::gapX() const
{
    return mGapX;
}

int QPixmapProvider::gapY() const
{
    return mGapY;
}

int QPixmapProvider::width() const
{
    return mWidth;
}

int QPixmapProvider::height() const
{
    return mHeight;
}

void QPixmapProvider::setOffsetX(int newOffsetX)
{
    mOffsetX = newOffsetX;
}

void QPixmapProvider::setOffsetY(int newOffsetY)
{
    mOffsetY = newOffsetY;
}

void QPixmapProvider::setGapX(int newGapX)
{
    mGapX = newGapX;
}

void QPixmapProvider::setGapY(int newGapY)
{
    mGapY = newGapY;
}

void QPixmapProvider::setWidth(int newWidth)
{
    mWidth = newWidth;
}

void QPixmapProvider::setHeight(int newHeight)
{
    mHeight = newHeight;
}
