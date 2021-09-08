#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <QObject>
#include <QVector>
#include <functional>

class GameScene;
class GameCharacter;

class EnemyAI : public QObject
{
    Q_OBJECT
public:
    template<typename _F> using function = std::function<_F>;
    using Action = std::function<void()>;
    EnemyAI(GameScene* game);
    void start();

    static Action moveAction(GameCharacter* ch, QPoint to);
    static Action attackAction(GameCharacter* src, GameCharacter* dst);
    static Action healAction(GameCharacter* src, GameCharacter* dst);


signals:
    void AITurnFinished();

protected:
    virtual QVector<function<void()>> makeStrategy() = 0;

private:
    GameScene* mGame;
};

#endif // ENEMYAI_H
