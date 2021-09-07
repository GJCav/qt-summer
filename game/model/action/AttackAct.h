#ifndef ATTACKACT_H
#define ATTACKACT_H

#include <GameCharAction.h>
#include <QObject>

class AttackAct : public GameCharAction
{
    Q_OBJECT
public:
    explicit AttackAct(QObject *parent = nullptr);
};

#endif // ATTACKACT_H
