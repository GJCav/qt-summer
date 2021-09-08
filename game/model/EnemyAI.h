#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <QObject>

class GameScene;

class EnemyAI : public QObject
{
    Q_OBJECT
public:
    EnemyAI(GameScene* game);

    void start();

signals:
    void AITurnFinished();

protected:


private:
    GameScene* mGame;
};

#endif // ENEMYAI_H
