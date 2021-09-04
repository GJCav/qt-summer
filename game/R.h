#ifndef R_H
#define R_H

#include <QtCore>
#include <QtWidgets>
#include "util/AsepriteObject.h"

namespace R{

void initResource();
QGraphicsView* gameView();
QGraphicsScene* gameScene();

}

#endif // R_H
