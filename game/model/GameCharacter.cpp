#include "GameCharacter.h"

GameCharacter::GameCharacter(QObject *parent) : QObject(parent)
{

}

void GameCharacter::attacked(const qreal power)
{

}

void GameCharacter::healed(const qreal power)
{

}

void GameCharacter::moveTo(const QPoint pos)
{

}

void GameCharacter::selected()
{

}

QVector<CharAction *> GameCharacter::requestActionMenu()
{
    return {};
}

CharAction::CharAction(QObject *parent) : QObject(parent)
{

}
