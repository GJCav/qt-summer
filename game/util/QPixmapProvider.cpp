#include "QPixmapProvider.h"

QPixmapProvider::QPixmapProvider()
{

}

void QPixmapProvider::setPixmap(const QPixmap &newPixmap)
{
    if((&newPixmap) == (&mPixmap))
        return;
    mPixmap = newPixmap;
    recalculate();
}
