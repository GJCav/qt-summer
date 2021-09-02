#include "util/QPixmapGirdSplitter.h"
#include "util/QPixmapAutoSplitter.h"

#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmapAutoSplitter provider(":/picture/ui.png");
    provider.setSplitThreshold(2);

//    QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
//    item->setPixmap(provider.subPixmapAt(5));
//    item->setScale(4);

//    QGraphicsScene scene;
//    scene.addItem(item);

//    QGraphicsView view(&scene);
//    view.show();

    provider.preview()->show();

    return a.exec();
}
