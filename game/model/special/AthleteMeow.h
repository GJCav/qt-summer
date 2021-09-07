#ifndef ATHLETEMEOW_H
#define ATHLETEMEOW_H

#include "model/GameCharacter.h"
#include <QObject>

class AthleteMeow : public GameCharacter
{
    Q_OBJECT
public:
    AthleteMeow(GameCharItem* item, GameScene* game, int role = CharacterRole::None);



    // GameCharacter interface
public:
    qreal speed() const override;
};

#endif // ATHLETEMEOW_H
