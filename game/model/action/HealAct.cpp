#include "HealAct.h"
#include <QRandomGenerator>

HealAct::HealAct(GameCharacter* actor, QObject *parent)
    : GameCharAction(actor, parent)
{
    this->setText("治疗");
}


void HealAct::reset()
{
    setEnabled(true);
}

void HealAct::process()
{
    auto game = mActor->game();
    connect(
        game,
        &GameScene::charSelected,
        this,
        &HealAct::targetSelected,
        Qt::SingleShotConnection
    );
    game->selectReachableCharacter(mActor->pos(), 2, 0, Qt::green, QColor(Qt::green).lighter());
}

void HealAct::cancel()
{
    mActor->game()->cancelSelectProcess();
}

void HealAct::targetSelected(GameCharacter *c)
{
    bool isHead = (QRandomGenerator::global()->generate() % 10) < 7;
    if(isHead > 0){
        c->healed(10);
    }else{
        c->attacked(10);
    }

    if(mButtonItem != nullptr) mButtonItem->hide();
    else{
        Q_ASSERT_X(false, "access HealAct::mButtonItem after it is destoried.", "HealAct::targetSelected");
    }
    setEnabled(false);
    endProcess();
}
