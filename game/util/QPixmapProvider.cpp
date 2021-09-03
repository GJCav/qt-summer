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

QGraphicsView *QPixmapProvider::preview(QWidget *parent)
{
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
