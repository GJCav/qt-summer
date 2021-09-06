#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Level.h"
#include "GameCharacter.h"
#include <QGraphicsScene>
#include <QObject>
#include <QVector>

class GameScene : public QGraphicsScene
{
    Q_OBJECT;
public:
    explicit GameScene(QObject *parent = nullptr);

private:
    Level *level;
    //QVector<GameCharacter*> characters;

};

#endif // GAMESCENE_H
