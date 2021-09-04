
#include "R.h"
#include "item/MeowKnightItem.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    R::initResource();

    auto scene = R::gameScene();
    auto meow = new MeowKnightItem("grey");
    scene->addItem(meow);
    meow->setAutoStop(false);
    meow->setPos(100, 100);
    meow->setScale(6);

    R::gameView()->show();

    return a.exec();
}
