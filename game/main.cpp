#include "QPixmapProvider.h"

#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmapProvider provider(":/picture/ui.png");
    provider.setOffsetX(10);
    provider.setOffsetY(19);
    provider.setGapX(10);
    provider.setGapY(10);
    provider.setHeight(64);
    provider.setWidth(64);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
    item->setPixmap(provider.pixmapAt(1, 4));
    item->setScale(4);

    QGraphicsScene scene;
    scene.addItem(item);

    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}
