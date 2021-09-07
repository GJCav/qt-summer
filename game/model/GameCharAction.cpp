#include "GameCharacter.h"
#include "GameCharAction.h"

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
