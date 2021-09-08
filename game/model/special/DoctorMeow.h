#ifndef DOCTORMEOW_H
#define DOCTORMEOW_H

#include "model/GameCharacter.h"
#include "model/action/HealAct.h"
#include <QObject>

class DoctorMeow :  public GameCharacter
{
    Q_OBJECT
public:
    DoctorMeow(GameCharItem* item, GameScene* game, int role = CharacterRole::None);

private:
    HealAct* mHealAct;

    // GameCharacter interface
public:
    QVector<GameCharAction *> requestActionMenu() override;
    QVector<QPixmap> requestIcons() override;


    // GameCharacter interface
public:
    void endTurn() override;

};

#endif // DOCTORMEOW_H
