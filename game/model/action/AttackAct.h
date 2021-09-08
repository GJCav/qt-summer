#ifndef ATTACKACT_H
#define ATTACKACT_H

#include "model/GameCharAction.h"
#include "model/GameCharacter.h"
#include <QObject>

class AttackAct : public GameCharAction
{
    Q_OBJECT
public:
    explicit AttackAct(GameCharacter* actor, QObject *parent = nullptr);

    // GameCharAction interface
    void reset() override;
    void cancel() override;



    int attackRangeMin() const;
    int attackRangeMax() const;

private:
    // TODO: 把GameCharacter的attack属性套上property，然后自动更新
    // 不用这么做了
    //int mAttackPower;
    int mAttackRangeMin = 0; // min <= target <= max
    int mAttackRangeMax = 1;

private slots:
    void targetSelected(GameCharacter *target);

    // GameCharAction interface
protected:
    void process() override;



};

#endif // ATTACKACT_H
