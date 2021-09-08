#include "GameCharacter.h"
#include "GameCharAction.h"
#include "model/HUD.h"

GameCharAction::GameCharAction(GameCharacter* actor, QObject *parent) : QAction(parent)
{
    mActor = actor;
    connect(this, &GameCharAction::triggered, this, &GameCharAction::callProcess);
}

ButtonItem *GameCharAction::buttonItem() const
{
    return mButtonItem;
}

void GameCharAction::setButtonItem(ButtonItem *newButtonItem)
{
    mButtonItem = newButtonItem;
}

void GameCharAction::process()
{

}

void GameCharAction::cancel()
{

}

void GameCharAction::endProcess()
{
    mButtonItem = nullptr;
    end();
}

bool GameCharAction::allowCancel() const
{
    return mAllowCancel;
}

void GameCharAction::setAllowCancel(bool newAllowCancel)
{
    mAllowCancel = newAllowCancel;
}

void GameCharAction::begin()
{
    //qDebug() << "CharAction: "<< text() << ", at: " << this;

    auto game = mActor->game();

    auto hud = game->getHUD();

    // 阻止选择一个操作后点击另一个操作，否则将导致mButtonItem被释放
    //qDebug() << "CharAction: "<< text() << ", at: " << this << ", close HUD";
    hud->setActBtnVisible(false);

    game->setAllowOpenHUD(false); // 阻止键盘打开HUD

    //qDebug() << "CharAction: "<< text() << ", at: " << this << ", disallow end turn.";
    hud->setAllowEndTurn(false);

    game->setProcessCharClick(false); // 阻止选择另一个角色，否则将导致mButtonItem被释放
    game->setAllowUnselectChar(false); // 阻止取消选择，同上

    if(mAllowCancel){
        connect(mActor->game(), &GameScene::escKeyPressed, this, &GameCharAction::callCancel);
        mHasCancelCnt = true;
    }
}

void GameCharAction::end()
{
    if(mHasCancelCnt){
        disconnect(mActor->game(), &GameScene::escKeyPressed, this, &GameCharAction::callCancel);
    }

    auto game = mActor->game();
    game->getHUD()->setActBtnVisible(true);
    game->setAllowOpenHUD(true);
    game->getHUD()->setAllowEndTurn(true);

    game->setProcessCharClick(true);
    game->setAllowUnselectChar(true);

    disconnect(mActor->game(), nullptr, this, nullptr);
}

void GameCharAction::callProcess() {
    //if(mActor->health() <= 0) return; // GameCharacter should handle this.
    begin();
    process();
}

void GameCharAction::callCancel()
{
    cancel();
    end();
}
