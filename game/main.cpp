
#include "R.h"
#include "model/GameScene.h"
#include "item/TextBoxItem.h"
#include "ui/HUDDesign.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

#include "model/scene/HelloScene.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

    GameScene *game = new HelloScene();
    game->init();

    QGraphicsView view;
    view.setScene(game);
    view.setSceneRect({0, 0, 1024, 768});
    view.show();

    view.setFixedSize(view.size());
    view.show();


//    HUDDesign h;
//    h.show();

    return a.exec();
}



















