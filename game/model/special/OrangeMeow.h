#ifndef ORANGEMEOW_H
#define ORANGEMEOW_H

#include "model/GameCharacter.h"
#include <QObject>

class OrangeMeow : public GameCharacter
{
    Q_OBJECT
public:
    explicit OrangeMeow(GameCharItem* item, GameScene* game, int role = CharacterRole::None);
};

#endif // ORANGEMEOW_H
