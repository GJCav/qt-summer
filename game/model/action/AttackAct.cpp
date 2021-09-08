#include "AttackAct.h"
#include "model/GameScene.h"

#include <QtGui>


AttackAct::AttackAct(GameCharacter* actor, QObject *parent)
    : GameCharAction(actor, parent)
{
    this->setText("攻击");
    //mAttackPower = actor->attackPower();
}

void AttackAct::targetSelected(GameCharacter *target)
{
    mActor->setTowards(target->pos().x() >= mActor->pos().x());
    mActor->attack();
    QTimer::singleShot(200, this, [this, target](){
        target->attacked(mActor->attackPower());
    });

    if(mButtonItem != nullptr) mButtonItem->hide();
    else{
        Q_ASSERT_X(false, "access AttackAct::mButtonItem after it is destoried.", "AttackAct::targetSelected");
    }

    setEnabled(false);
    endProcess();
}

void AttackAct::process()
{
    auto game = mActor->game();
    connect(
        game,
        &GameScene::charSelected,
        this,
        &AttackAct::targetSelected,
        Qt::SingleShotConnection
    );
    game->selectReachableCharacter(mActor->pos(), mAttackRangeMax, mAttackRangeMin);
}


void AttackAct::reset()
{
    setEnabled(true);
}


void AttackAct::cancel()
{
    mActor->game()->cancelSelectProcess();
}
