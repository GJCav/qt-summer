
#include "R.h"
#include "item/MeowKnightItem.h"
#include "test/TestWindow.h"
#include "util/QPixmapGirdSplitter.h"
#include "model/Level.h"
#include "item/PropItem.h"
#include "model/GameCharacter.h"
#include "item/SelectIndicatorItem.h"
#include "ui/HUD.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

    QGraphicsScene scene;
    Level level;
    level.initLevel(16, 12);
    level.setStonePath(QRect(1, 2, 5, 4));
    level.setWallRect(QRect(0, 0, 16, 12));
    level.setScene(&scene);

    PropItem chest(PropItem::PropType::Chest);
    PropItem magic(PropItem::PropType::Magic);
    chest.setPos(100, 300);
    magic.setPos(200, 400);
    scene.addItem(&chest);
    scene.addItem(&magic);

    MeowKnightItem meow("grey");
    scene.addItem(&meow);
    meow.setPos(0, 0);
    meow.setScale(3.5);

    GameCharacter ch(&meow);

    HUD *hud = new HUD;
    QGraphicsProxyWidget p;
    p.setWidget(hud);
    scene.addItem(&p);

    QGraphicsView view;
    view.setScene(&scene);
    view.setSceneRect({0, 0, 1024, 768});

    view.show();


    return a.exec();
}



















