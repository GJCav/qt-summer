#include "util/QPixmapGirdSplitter.h"

#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmapGirdSplitter provider(":/picture/ui.png");
    provider.setOffsetX(10);
    provider.setOffsetY(19);
    provider.setGapX(10);
    provider.setGapY(10);
    provider.setHeight(64);
    provider.setWidth(64);
    provider.recalculate();

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
    item->setPixmap(provider.subPixmapAt(5));
    item->setScale(4);

    QGraphicsScene scene;
    scene.addItem(item);

    QGraphicsView view(&scene);
    view.show();

    provider.preview()->show();

    return a.exec();
}
