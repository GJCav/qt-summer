#include "MoveAct.h"

MoveAct::MoveAct(GameCharacter* actor, QObject *parent) : GameCharAction(actor, parent)
{
    this->setText("移动");
}

void MoveAct::targetSelected(QPoint pos)
{
    mActor->moveTo(pos);
    if(mButtonItem != nullptr) mButtonItem->hide();
    else{
        Q_ASSERT_X(false, "access MoveAct::mButtonItem after it is destoried.", "MoveAct::targetSelected");
    }
    setEnabled(false);
    endProcess();
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


void MoveAct::reset()
{
    //mButtonItem->show(); 按钮被释放掉了QAQ
    setEnabled(true);
}

void MoveAct::cancel()
{
    mActor->game()->cancelSelectProcess();
}
