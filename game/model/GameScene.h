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
    constexpr static int GroundEffect = 3000; // 太低会让点击时间传递到character
    constexpr static int UIIndicatorZValue = 3000;

    explicit GameScene(QObject *parent = nullptr);

    void init(); //remember to call this;

    Level *level() const;
    const QVector<GameCharacter *> &chars() const;
    const QVector<GameProp *> &props() const;

    void addProp(GameProp* item);
    void addChar(GameCharacter* ch);

    GameProp* propAt(const QPoint h) const;
    GameCharacter* charAt(const QPoint h) const;

    //inline int curTurn() {return mTurn;}

    void selectMoveDestination(
        const QPoint origin,
        const int max,
        const int min=0
    ); // min < dest <= max

    void selectReachableCharacter(
        const QPoint origin,
        const int max,
        const int min=0
    );

    void cancelSelectProcess(); // 取消 selectMoveDestination 和 selectReachableCharacter 的显示

    HUD *getHUD() const;

    bool processCharClick() const;
    void setProcessCharClick(bool newEnableCharClick);

    bool allowUnselectChar() const;
    void setAllowUnselectChar(bool newAllowUnselectChar);

    bool allowOpenHUD() const;
    void setAllowOpenHUD(bool newAllowOpenHUD);



public slots:
    void nextTurn();

private slots:
    void charClick(GameCharacter* src);
    void endTurn();
    void charSelectedChange(bool slt); // 用于取消选择角色

signals:
    void charClicked(GameCharacter* target);
    void moveDestSelected(QPoint pos);
    void charSelected(GameCharacter* target);
    void escKeyPressed();

protected:
    Level *mLevel = nullptr;
    QVector<GameProp*> mProps;
    QVector<GameCharacter*> mChars;
    HUD *hud = nullptr;

//    /**
//     * @brief mState
//     *   0: 普通状态。选择人物，显示其属性，弹出HUD，右侧显示操作按钮。
//     *   1: 操作状态。操作按钮显示“确认\取消”，清空原有选择，显示辅助地标。
//     *   2: 操作确认。播放动画，忽略所有鼠标动作。
//     *   3: 敌方回合。不显示右侧操作按钮。
//     */
    int mState = 0;
    int mTurn = 0; // 回合编号

    // 选择相关
    // TODO: 未来计划不再使用click信号？免得select和click各种重复
    bool mProcessCharClick = true;
    GameCharacter* mLastClickChar = nullptr; // 防止重复点击同一个角色
    bool mAllowUnselectChar = true;

    // 其他开关
    bool mAllowOpenHUD = true;

    virtual void charClickedEvent(GameCharacter* src);

    virtual void endTurnEvent();

    virtual void initLevel();
    virtual void initPropItems();
    virtual void initChars();
    virtual void initHUD();

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsItemGroup* mSltIndicate = nullptr;

    void deleteItemGroup(QGraphicsItemGroup* &group);
};

#endif // GAMESCENE_H
