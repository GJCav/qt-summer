#ifndef THIRDSCENE_H
#define THIRDSCENE_H

#include "model/GameScene.h"
#include "model/special/DoctorMeow.h"
#include "model/special/BossMeow.h"
#include <QObject>

class ThirdScene : public GameScene
{
public:
    explicit ThirdScene(QObject *parent = nullptr);

private:
    DoctorMeow *mDocMeow;
    BossMeow *mBossMeow;

    // GameScene interface
protected:
    void initLevel() override;
    void initPropItems() override;
    void initChars() override;
    void initChore() override;
    int successOrFailed() override;
};

#endif // THIRDSCENE_H
