#ifndef GAMECHARACTION_H
#define GAMECHARACTION_H

#include "item/hud/ButtonItem.h"
#include <QAction>
#include <QObject>
#include <QWidget>

class GameCharacter;

// 血的教训，一定要在动作完成后解除所有到自己slot的链接，否则可能会莫名其妙多次调用
// 这个特别容易忘，所以基类会自动取消当前 GameScene 到自己的所有链接
class GameCharAction : public QAction
{
    Q_OBJECT

public:
    //explicit GameCharAction(const QString& text, QObject *parent = nullptr);
    explicit GameCharAction(GameCharacter* actor, QObject *parent = nullptr);

    ButtonItem *buttonItem() const;
    void setButtonItem(ButtonItem *newButtonItem);

    virtual void reset() = 0;

    bool allowCancel() const;
    void setAllowCancel(bool newAllowCancel);

protected:
    GameCharacter *mActor;
    ButtonItem *mButtonItem = nullptr;

    /**
     * @brief process
     * 如果正常结束，一定要调用endProcess()解除占用。
     * 如果是按Esc取消，会自动解除占用，不要再调用endProcess();
     * 如果禁止Esc取消，调用setAllowCancel(false);
     */
    virtual void process();
    virtual void cancel();

    // important! call this in subclasses.
    void endProcess();

private:
    bool mAllowCancel = true;
    bool mHasCancelCnt = false;

    void begin();
    void end();

private slots:
    void callProcess();
    void callCancel();
};

#endif // GAMECHARACTION_H
