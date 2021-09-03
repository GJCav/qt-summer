#ifndef QPIXMAPSEQUENCE_H
#define QPIXMAPSEQUENCE_H


#include "QPixmapProvider.h"
#include <QtCore>
#include <QtWidgets>

class QPixmapFileSeq
{
public:
    QPixmapFileSeq(const QString prefix, const int st, const int ed, const QString suffix);



    const QString &prefix() const;
    void setPrefix(const QString &newPrefix);
    int st() const;
    void setSt(int newSt);
    int ed() const;
    void setEd(int newEd);
    const QString &suffix() const;
    void setSuffix(const QString &newSuffix);
    const QVector<QPixmap> &pixmapList() const;

private:
    QString mPrefix;
    int mSt, mEd;
    QString mSuffix;
    QVector<QPixmap> mPixmapList;

    inline void recalculate() { calculateRects(); }
    const QString composePath(const int i) const;

    // QPixmapProvider interface
protected:
    void calculateRects();


    // QPixmapProvider interface
public:
    QGraphicsView *preview(QWidget *parent = nullptr);
};

#endif // QPIXMAPSEQUENCE_H
