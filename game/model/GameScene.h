#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Level.h"
#include "item/PropItem.h"
#include "item/LevelCellItem.h"
#include <QGraphicsScene>
#include <QObject>
#include <QVector>

class GameProp;
class GameCharacter;
class HUD;

class GameScene : public QGraphicsScene
{
    Q_OBJECT;
public:
    constexpr static int CellSize = LevelCellItem::CellSize;
    explicit GameScene(QObject *parent = nullptr);

    void init(); //remember to call this;

    Level *level() const;
    const QVector<GameCharacter *> &chars() const;
    const QVector<GameProp *> &props() const;

    void addProp(GameProp* item);
    void addChar(GameCharacter* ch);


protected:
    Level *mLevel = nullptr;
    QVector<GameProp*> mProps;
    QVector<GameCharacter*> mChars;
    HUD *hud = nullptr;

    /**
     * @brief mState
     *   0: 普通状态。选择人物，显示其属性，弹出HUD，右侧显示操作按钮。
     *   1: 操作状态。操作按钮显示“确认\取消”，清空原有选择，显示辅助地标。
     *   2: 操作确认。播放动画，忽略所有鼠标动作。
     *   3: 敌方回合。不显示右侧操作按钮。
     */
    int mState = 0;

    virtual void charClickedEvent(GameCharacter* src);

    virtual void initLevel();
    virtual void initPropItems();
    virtual void initChars();
    virtual void initHUD();

private slots:
    void charClicked(GameCharacter* src);


    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
