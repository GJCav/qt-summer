#include "MoveAct.h"

MoveAct::MoveAct(GameCharacter* actor, QObject *parent) : GameCharAction(actor, parent)
{
    this->setText("移动");
}

void MoveAct::targetSelected(QPoint pos)
{
    mActor->moveTo(pos);
    mLastTurn = mActor->game()->curTurn();
    mButtonItem->hide();
    setEnabled(false);
}

void MoveAct::process()
{
    auto game = mActor->game();
    connect(
        game,
        &GameScene::moveDestSelected,
        this,
        &MoveAct::targetSelected,
        Qt::SingleShotConnection
    );
    game->selectMoveDestination(mActor->pos(), mActor->speed());
}
