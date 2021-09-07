#ifndef HEALACT_H
#define HEALACT_H

#include "model/GameCharAction.h"
#include "model/GameCharacter.h"
#include "model/GameScene.h"
#include <QObject>

class HealAct : public GameCharAction
{
    Q_OBJECT
public:
    explicit HealAct(GameCharacter* actor, QObject *parent = nullptr);


    // GameCharAction interface
public:
    void reset() override;


protected:
    void process() override;
    void cancel() override;

private:
    void targetSelected(GameCharacter *target);
};

#endif // HEALACT_H
