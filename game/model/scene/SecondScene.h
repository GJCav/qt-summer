#ifndef SECONDSCENE_H
#define SECONDSCENE_H

#include "model/GameScene.h"
#include <QObject>

class SecondScene : public GameScene
{
    Q_OBJECT
public:
    explicit SecondScene(QObject *parent = nullptr);



    // GameScene interface
protected:
    void initLevel() override;
    void initPropItems() override;
    void initChars() override;
    void initChore() override;
};

#endif // SECONDSCENE_H
