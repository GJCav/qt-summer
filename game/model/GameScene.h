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
    constexpr static int GameWidth = 16;
    constexpr static int GameHeight = 12;

    explicit GameScene(QObject *parent = nullptr);

    void init(); //remember to call this;

    Level *level() const;
    const QVector<GameCharacter *> &chars() const;
    const QVector<GameProp *> &props() const;

    void addProp(GameProp* item);
    void addChar(GameCharacter* ch);

    GameProp* propAt(const QPoint h) const;
    GameCharacter* charAt(const QPoint h) const;

    inline int curTurn() {return mTurn;}

public slots:
    void nextTurn();
    void selectMoveDestination(const QPoint origin, const int len, const int min=0); // min < dest <= len

private slots:
    void charClick(GameCharacter* src);

signals:
    void charClicked(GameCharacter* target);
    void moveDestSelected(QPoint pos);

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
    int mTurn = 0; // 回合编号

    virtual void charClickedEvent(GameCharacter* src);

    virtual void initLevel();
    virtual void initPropItems();
    virtual void initChars();
    virtual void initHUD();

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsItemGroup* mSltIndicate = nullptr;

    void deleteItemGroup(QGraphicsItemGroup* group);
};

#endif // GAMESCENE_H
