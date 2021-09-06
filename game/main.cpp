
#include "R.h"
#include "item/MeowKnightItem.h"
#include "test/TestWindow.h"
#include "util/QPixmapGirdSplitter.h"
#include "model/Level.h"
#include "item/PropItem.h"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

class RectItem : public QGraphicsRectItem {
public:
    RectItem(int x, int y, int w, int h) : QGraphicsRectItem(x, y, w, h){
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }

    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

QVariant RectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene()){
        QPoint newPos = value.toPoint();
        qDebug("inner %d", newPos.x());
    }
    return QGraphicsRectItem::itemChange(change, value);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    R::initResource();

//    TestWindow w;
//    w.show();

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
    meow.setPos(500, 500);
    meow.setScale(4);

    QGraphicsView view;
    view.setScene(&scene);
    view.setSceneRect({0, 0, 1024, 768});

    view.show();

//    QGraphicsView view;
//    view.show();
//    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);

//    QGraphicsScene *e = new QGraphicsScene;
//    view.setScene(e);

//    e->setSceneRect(0, 0, 500, 600);
//    e->addRect(0, 0, 500, 600);

//    QGraphicsRectItem *r = new QGraphicsRectItem(0, 0, 100, 20);
//    r->setPos(100, 200);
//    e->addItem(r);
//    r->setFlag(QGraphicsItem::ItemIsMovable);


//    QTimer *t = new QTimer;
//    t->callOnTimeout([&](){
//        qDebug("%d", r->scenePos().y());
//    });
//    t->start(500);

    return a.exec();
}



















