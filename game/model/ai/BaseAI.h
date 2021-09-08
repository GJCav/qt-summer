#ifndef BASEAI_H
#define BASEAI_H

#include "model/EnemyAI.h"
#include "model/GameScene.h"
#include <QObject>

class BaseAI : public EnemyAI
{
    Q_OBJECT
public:
    BaseAI(GameScene *game);

    // EnemyAI interface
protected:
    QVector<function<void ()> > makeStrategy() override;

private:

};

#endif // BASEAI_H
