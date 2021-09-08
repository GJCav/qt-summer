#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <QObject>
#include <QVector>
#include <functional>

class GameScene;

class EnemyAI : public QObject
{
    Q_OBJECT
public:
    template<typename _F> using function = std::function<_F>;
    EnemyAI(GameScene* game);
    void start();

signals:
    void AITurnFinished();

protected:
    virtual QVector<function<void()>> makeStrategy() = 0;

private:
    GameScene* mGame;
};

#endif // ENEMYAI_H
