#include "QPixmapFileSeq.h"
#include <QFileInfo>

QPixmapFileSeq::QPixmapFileSeq(
        const QString prefix,
        const int st,
        const int ed,
        const QString suffix
        ) : mPrefix(prefix), mSt(st), mEd(ed), mSuffix(suffix)
{
    recalculate();
}

const QString &QPixmapFileSeq::prefix() const
{
    return mPrefix;
}

void QPixmapFileSeq::setPrefix(const QString &newPrefix)
{
    if(mPrefix == newPrefix) return;
    mPrefix = newPrefix;
    recalculate();
}

int QPixmapFileSeq::st() const
{
    return mSt;
}

void QPixmapFileSeq::setSt(int newSt)
{
    if(mSt == newSt) return;
    mSt = newSt;
    recalculate();
}

int QPixmapFileSeq::ed() const
{
    return mEd;
}

void QPixmapFileSeq::setEd(int newEd)
{
    if(mEd == newEd) return;
    mEd = newEd;
    recalculate();
}

const QString &QPixmapFileSeq::suffix() const
{
    return mSuffix;
}

void QPixmapFileSeq::setSuffix(const QString &newSuffix)
{
    if(mSuffix == newSuffix) return;
    mSuffix = newSuffix;
    recalculate();
}

const QVector<QPixmap> &QPixmapFileSeq::pixmapList() const
{
    return mPixmapList;
}

const QString QPixmapFileSeq::composePath(const int i) const
{
    QString s = mPrefix + QString::number(i) + mSuffix;
    return s;
}

void QPixmapFileSeq::calculateRects()
{
    for(int i = mSt;i < mEd;i++){
        const QString path = composePath(i);
        if(!QFileInfo::exists(path)) return;
    }

    mPixmapList.clear();

    for(int i = mSt;i < mEd;i++){
        const QString path = composePath(i);
        QPixmap newPixmap(path);
        newPixmap.toImage().format();
        mPixmapList.append(newPixmap);
    }
}

QGraphicsView *QPixmapFileSeq::preview(QWidget *parent)
{
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);


    int y = 0;
    foreach(const QPixmap& pixmap, mPixmapList){
        auto item = scene->addPixmap(pixmap);
        item->setPos(0, y);
        y += pixmap.height();
        y += 10;
    }

    return view;
}















