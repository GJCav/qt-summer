#ifndef MOVEACT_H
#define MOVEACT_H

#include "model/GameCharAction.h"
#include "model/GameCharacter.h"
#include "model/GameScene.h"
#include <QObject>

class MoveAct : public GameCharAction
{
    Q_OBJECT
public:
    explicit MoveAct(GameCharacter* actor, QObject *parent = nullptr);

    // GameCharAction interface
    void reset() override;
    void cancel() override;

    int getSpeedMin() const;
    void setSpeedMin(int newSpeedMin);

private slots:
    void targetSelected(QPoint pos);

    // GameCharAction interface
protected:
    void process() override;

private:
    int speedMin = 0;
};

#endif // MOVEACT_H
