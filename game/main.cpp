
#include "R.h"
#include "model/GameScene.h"
#include "ui/HUDDesign.h"
#include "item/CellIndicatorItem.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

    GameScene *game = new GameScene();
    game->init();

    QGraphicsView view;
    view.setScene(game);
    view.setSceneRect({0, 0, 1024, 768});
    view.show();



//    HUDDesign h;
//    h.show();

    return a.exec();
}



















