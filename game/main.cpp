
#include "R.h"
#include "model/GameScene.h"
#include "item/TextBoxItem.h"
#include "ui/HUDDesign.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

//    GameScene *game = new GameScene();
//    game->init();

//    QGraphicsView view;
//    view.setScene(game);
//    view.setSceneRect({0, 0, 1024, 768});
//    view.show();

    TextBoxItem *t = new TextBoxItem();
    t->setHtml("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
    t->setColor(Qt::green);
    t->setFontPointSize(24);

    QObject::connect(t, &TextBoxItem::clicked, [](){
        qDebug("asdfasdfasdf");
    });

    QGraphicsScene scene;
    scene.addItem(t);

    QGraphicsView view;
    view.setScene(&scene);

    view.show();


//    HUDDesign h;
//    h.show();

    return a.exec();
}



















