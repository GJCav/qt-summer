#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "item/GameCharItem.h"

#include <QObject>
#include <QVector>
#include <QGraphicsObject>
#include <QPoint>
#include <QAction>

class GameScene;
class GameCharAction;
class MoveAct;
class AttackAct;

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
    explicit GameCharacter(GameCharItem* item, GameScene* game, int role = CharacterRole::None);

    void setCharRole(const int role);
    inline int charRole() const {return mRole;}

    // animation player
    virtual void attack();
    virtual void attacked(const qreal power);
    virtual void healed(const qreal power);
    virtual void moveTo(const QPoint pos); // this plays animation, but setPos doesnt.
    inline void moveTo(int x, int y) {moveTo({x, y});}
    virtual void setPos(const QPoint pos);
    inline void setPos(int x, int y) {setPos({x, y});}
    virtual void die();
    virtual void dodge();
    virtual void setTowards(bool towardRight);

    virtual QVector<QPixmap> requestIcons();
    virtual QVector<GameCharAction*> requestActionMenu();

    // game position
    inline const QPoint pos() const { return mPos; }
    GameCharItem *charItem() const;

    // property getter and setter
    // use getter as default, because it will calculate special effects.
    const QString &name() const;
    void setName(const QString &newName);
    virtual qreal health() const;
    virtual qreal speed() const;
    virtual qreal defensivePower() const;
    virtual qreal lucky() const;
    virtual qreal attackPower() const;
    void setAttackPower(qreal newAttackPower);
    void setHealth(qreal newHealth);
    void setSpeed(qreal newSpeed);
    void setDefensivePower(qreal newDefensivePower);
    void setLucky(qreal newLucky);

    GameScene *game() const;
    virtual void endTurn();

    MoveAct *moveAct() const;

    AttackAct *attackAct() const;

public slots:
    //virtual void selected(bool slt);
    virtual void click(GameCharItem*);

signals:
    void clicked(GameCharacter* self);
    void selectedChange(bool slt);

protected:
    QString mName;
    qreal mRole = CharacterRole::None;
    qreal mHealth = 30;
    qreal mSpeed = 4;
    qreal mDefensivePower = 0;
    qreal mAttackPower = 5; // this is default attack power;
    qreal mLucky = 5; // mLucky / 100 == dodge(miss) percentage
    GameCharItem *mCharItem;

    GameScene *mGame;
    QPoint mPos; // position on the GameScene;

    // default actions
    MoveAct* mMoveAct;
    AttackAct* mAttackAct;

private:


    void initDefaultAction();

};

#endif // GAMECHARACTER_H
