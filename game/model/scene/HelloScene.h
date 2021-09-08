#ifndef HELLOSCENE_H
#define HELLOSCENE_H

#include "model/GameScene.h"
#include <QObject>

// 开始界面
class HelloScene : public GameScene
{
    Q_OBJECT
public:
    explicit HelloScene(QObject *parent = nullptr);


    // GameScene interface
protected:

    void initHUD() override;
    void initChore() override;
    void initLevel() override;



    // QGraphicsScene interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // GameScene interface
protected:
    void initPropItems() override;
};

#endif // HELLOSCENE_H
