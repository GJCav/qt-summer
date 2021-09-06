#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "item/GameCharItem.h"
#include <QObject>
#include <QVector>
#include <QGraphicsObject>
#include <QPoint>

class CharAction;

class GameCharacter : public QObject
{
    Q_OBJECT
public:
    struct CharacterRole {
        constexpr static int None = 0;
        constexpr static int Player1 = 100;
        constexpr static int Player2 = 200; // player 2-4 has no use currently.
        constexpr static int Player3 = 300;
        constexpr static int Player4 = 400;

        constexpr static int Enemy = 1000;
    };


public:
    explicit GameCharacter(GameCharItem* item, QObject *parent = nullptr);

    virtual void attacked(const qreal power);
    virtual void healed(const qreal power);
    virtual void moveTo(const QPoint pos); // this plays animation, but setPos doesnt.
    virtual void setPos(QRect pos);
    virtual void die();
    virtual void dodge();

public slots:
    virtual void selected(bool slt);

signals:

protected:
    virtual QVector<CharAction*> requestActionMenu();

private:
    qreal mRole = CharacterRole::None;
    qreal mHealth = 20;
    qreal mSpeed = 2;
    qreal mDefensivePower = 0;
    qreal mLucky = 5; // mLucky / 100 == dodge(miss) percentage
    QVector<CharAction*> mActions;
    GameCharItem *mCharItem;

    QPoint mPos; // position on the GameScene;

};


class CharAction : public QObject{
    Q_OBJECT
public:
    CharAction(QObject *parent = nullptr);

protected:
    int mTargetCount = 0;
    GameCharacter* source;
    QVector<GameCharacter*> target;
};

#endif // GAMECHARACTER_H
