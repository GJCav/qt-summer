#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Level.h"
#include "item/PropItem.h"
#include "item/LevelCellItem.h"
#include "item/MeowKnightItem.h"
#include "item/TextBoxItem.h"
#include "GameCharacter.h"
#include <QGraphicsScene>
#include <QObject>
#include <QVector>
#include <tuple>

class GameProp;
class HUD;
class EnemyAI;

using std::tuple;

class GameScene : public QGraphicsScene
{
    Q_OBJECT;
public:
    constexpr static int CellSize = LevelCellItem::CellSize;
    constexpr static int GameWidth = 16;
    constexpr static int GameHeight = 12;
    constexpr static int GroundEffect = 3000; // 太低会让点击事件传递到character
    constexpr static int UIIndicatorZValue = 3000;

    explicit GameScene(QObject *parent = nullptr);

    void init(); //remember to call this

    Level *level() const;
    const QVector<GameCharacter *> &chars() const;
    const QVector<GameProp *> &props() const;

    void addProp(GameProp* item);
    void addChar(GameCharacter* ch);

    template<typename MeowType>
    typename std::enable_if<
        std::is_base_of<GameCharacter, MeowType>::value,
        MeowType*
    >::type createPlayerChar(){
        MeowKnightItem *meow = new MeowKnightItem("grey");
        MeowType *ch = new MeowType(meow, this, GameCharacter::CharacterRole::Player1);
        return ch;
    }

    template<typename MeowType>
    typename std::enable_if<
        std::is_base_of<GameCharacter, MeowType>::value,
        MeowType*
    >::type createEnemyChar(){
        MeowKnightItem *meow = new MeowKnightItem("yellow");
        MeowType *ch = new MeowType(meow, this, GameCharacter::CharacterRole::Enemy);
        return ch;
    }


    GameProp* propAt(const QPoint h) const;
    GameCharacter* charAt(const QPoint h) const;
    inline LevelCellItem* cellAt(const QPoint h) const {return mLevel->cellRows()[h.y()][h.x()];}
    inline LevelCellItem* cellAt(int x, int y) const {return cellAt({x, y});}

    //inline int curTurn() {return mTurn;}

    enum class MoveDestType : int{
        Unreachable = 0,
        Invalid = 1,
        Valid = 2
    };
    QVector<tuple<QPoint, MoveDestType>> listMoveDestination(
        const QPoint origin,
        const int max,
        const int min=0
    );
    void selectMoveDestination(
        const QPoint origin,
        const int max,
        const int min=0
    ); // min < dest <= max

    enum class ReachCharType : int {
        Unreachable = 0,
        Invalid = 1,
        Valid = 2
    };
    QVector<tuple<QPoint, ReachCharType>> listReachableCharacterPos(
        const QPoint origin,
        const int max,
        const int min=0
    );
    void selectReachableCharacter(
        const QPoint origin,
        const int max,
        const int min=0,
        QColor targetColor = {Qt::red},
        QColor lightColor = {240, 138, 140}
    );

    void cancelSelectProcess(); // 取消 selectMoveDestination 和 selectReachableCharacter 的显示

    HUD *getHUD() const;

    bool processCharClick() const;
    void setProcessCharClick(bool newEnableCharClick);

    bool allowUnselectChar() const;
    void setAllowUnselectChar(bool newAllowUnselectChar);

    bool allowOpenHUD() const;
    void setAllowOpenHUD(bool newAllowOpenHUD);

    inline bool validGamePos(const QPoint p){
        return !(p.x() < 0 || p.x() >= GameWidth || p.y() < 0 || p.y() >= GameHeight);
    }
    inline bool validGamePos(int x, int y) { return validGamePos({x, y});}

    void txtBoxSeries(QVector<TextBoxItem*> arr);

public slots:
    //void nextTurn(); //用endTurn代替

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
    EnemyAI *mAI = nullptr;

//    /**
//     * @brief mState
//     *   0: 普通状态。选择人物，显示其属性，弹出HUD，右侧显示操作按钮。
//     *   //1: 操作状态。操作按钮显示“确认\取消”，清空原有选择，显示辅助地标。 弃用
//     *   //2: 操作确认。播放动画，忽略所有鼠标动作。  弃用
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

    // 在点击结束回合和AI操作结束后调用，根据结果决定下一步行为
    // return 0: 继续回合, 1: 胜利，2: 失败
    virtual int successOrFailed();
    virtual void gameSuccess();// 成功后调用
    virtual void gameFailed(); // 失败后调用

    virtual void charClickedEvent(GameCharacter* src);

    virtual void endTurnEvent();
    virtual void beginAITurn(); // call manually if override
    virtual void endAITurn();// call manually if override

    virtual void initLevel();
    virtual void initPropItems();
    virtual void initChars();
    virtual void initHUD();
    virtual void initAI();
    virtual void initChore(); // 杂项初始化

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsItemGroup* mSltIndicate = nullptr;

    QSoundEffect *mFailSound;
    QSoundEffect *mSuccessSound;

    void deleteItemGroup(QGraphicsItemGroup* &group);

private slots:
    void charClick(GameCharacter* src);
    void endTurn();
    void AITurnEnded();
    void charSelectedChange(bool slt); // 用于取消选择角色
};

#endif // GAMESCENE_H
