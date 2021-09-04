#include "R.h"

namespace {
QGraphicsScene *defaultScene;
QGraphicsView *defaultView;

}

namespace R{
void initResource()
{
    defaultScene = new QGraphicsScene();
    defaultView = new QGraphicsView();

    defaultView->setScene(defaultScene);
    defaultView->setSceneRect(0, 0, 800, 600);

}

QGraphicsView *gameView()
{
    return defaultView;
}

QGraphicsScene *gameScene()
{
    return defaultScene;
}
}



