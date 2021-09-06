
#include "R.h"
#include "item/MeowKnightItem.h"
#include "test/TestWindow.h"
#include "util/QPixmapGirdSplitter.h"
#include "model/Level.h"
#include "item/PropItem.h"
#include "model/GameCharacter.h"
#include "item/SelectIndicatorItem.h"
#include "ui/HUDDesign.h"
#include "model/HUD.h"
#include "item/hud/ButtonItem.h"
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

    HUD hud(&scene);
    QVector<QPixmap> iconPixs;
    for(int i = 0;i < 5;i++){
        iconPixs.append(R::IconPixmap->copy(i*32, 0, 32, 32));
    }
    hud.setIcons(iconPixs);

    QVector<QAction*> actions;
    for(int i = 0;i < 4;i++){
        QAction *act = new QAction();
        act->setText(QString::number(i));
        QObject::connect(act, &QAction::triggered, [i](bool t){
            qDebug() << i;
        });
        actions.append(act);
    }
    hud.setActBtns(actions);


    QGraphicsView view;
    view.setScene(&scene);
    view.setSceneRect({0, 0, 1024, 768});
    view.show();

    HUDDesign h;
    h.show();

    return a.exec();
}



















