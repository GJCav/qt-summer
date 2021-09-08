#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <QObject>
#include <QVector>

class GameScene;
class GameCharacter;

class EnemyAI : public QObject
{
    Q_OBJECT
public:
    EnemyAI(GameScene* game);

    virtual void start() = 0;

    GameScene *game() const;

signals:
    void AITurnFinished();

private:
    GameScene* mGame;
};

#endif // ENEMYAI_H
