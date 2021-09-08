#ifndef BASEAI_H
#define BASEAI_H

#include "model/EnemyAI.h"
#include "model/GameScene.h"
#include "model/GameCharacter.h"
#include "QVector"
#include <QObject>

class BaseAI : public EnemyAI
{
    Q_OBJECT
public:
    BaseAI(GameScene *game);

    // EnemyAI interface
    void start() override;

private:
    QVector<GameCharacter*> enemies;
    QVector<bool> acted;
    int stage = 0;
    GameCharacter* moreTryEnemy = nullptr;

    bool tryAttack(GameCharacter* enemy);
    bool tryMove(GameCharacter* enemy);

private slots:
    void nextAction();


};

#endif // BASEAI_H
