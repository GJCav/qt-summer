#ifndef FIRSTSCENE_H
#define FIRSTSCENE_H

#include "model/GameScene.h"

class FirstScene : public GameScene
{
public:
    explicit FirstScene(QObject *parent = nullptr);

    // GameScene interface
protected:
    void initLevel() override;
    void initPropItems() override;
    void initChars() override;
    void initChore() override;
};

#endif // FIRSTSCENE_H
