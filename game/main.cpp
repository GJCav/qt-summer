
#include "R.h"
#include "item/MeowKnightItem.h"
#include "test/TestWindow.h"
#include "util/QPixmapGirdSplitter.h"
#include "model/Level.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

//    TestWindow w;
//    w.show();

//    QGraphicsScene scene;
//    Level level;
//    level.initLevel(16, 12);
//    level.setStonePath(QRect(1, 2, 5, 4));
//    level.setWallRect(QRect(0, 0, 16, 12));
//    level.setScene(&scene);

//    QGraphicsView view;
//    view.setScene(&scene);
//    view.setSceneRect({0, 0, 1024, 768});

//    view.show();

    return a.exec();
}
