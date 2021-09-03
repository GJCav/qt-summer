#include "util/QPixmapGirdSplitter.h"
#include "util/QPixmapAutoSplitter.h"
#include "util/QPixmapFileSeq.h"
#include "util/AsepriteObject.h"

#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QGraphicsScene scene;
//    QGraphicsView view;
//    view.setScene(&scene);


    AsepriteObject item;
    item.setJsonPath(":/asset/Meow Knight/Meow_Knight.json");
    item.setTexturePixmap(QPixmap(":/asset/Meow Knight/grey.png"));



    return a.exec();
}
