#ifndef BOSSMEOW_H
#define BOSSMEOW_H

#include "model/GameCharacter.h"

class BossMeow : public GameCharacter
{
    Q_OBJECT
public:
    BossMeow(GameScene* game);



    // GameCharacter interface
public:
    void endTurn() override;

private:
    int mTurnCount = 0;
};

#endif // BOSSMEOW_H
