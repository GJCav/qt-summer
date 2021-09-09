#include "GameCharacter.h"
#include "item/PopupTextItem.h"
#include "R.h"
#include "GameCharAction.h"
#include "action/MoveAct.h"
#include "action/AttackAct.h"
#include "model/GameProp.h"
#include "GameScene.h"
#include <QtGlobal>
#include <QtCore>
#include <QtGui>
#include <QtConcurrent/QtConcurrent>

GameCharacter::GameCharacter(GameCharItem* item, GameScene* game, int role)
    : QObject(game)
{
    mRole = role;
    mGame = game;

    mCharItem = item;
    mCharItem->setScale(3.5);
    mCharItem->setFlag(QGraphicsItem::ItemIsSelectable);
    connect(mCharItem, &GameCharItem::selectedChange, this, &GameCharacter::selectedChange);
    connect(mCharItem, &GameCharItem::clicked, this, &GameCharacter::click);

    initDefaultAction();

    setName("喵");

    mTakeDamageSound = new QSoundEffect(this);
    mFriendSound = new QSoundEffect(this);
    mEnemySound = new QSoundEffect(this);
    mHealedSound = new QSoundEffect(this);
    mSwordSound = new QSoundEffect(this);

    mTakeDamageSound->setSource(QUrl("qrc:/asset/sound/gethurt.wav"));
    mFriendSound->setSource(QUrl("qrc:/asset/sound/friend.wav"));
    mEnemySound->setSource(QUrl("qrc:/asset/sound/enemy.wav"));
    mHealedSound->setSource(QUrl("qrc:/asset/sound/healed.wav"));
    mSwordSound->setSource(QUrl("qrc:/asset/sound/Sword.wav"));
}

void GameCharacter::attacked(const qreal power)
{
    if(mHealth <= 0) return;

    bool canDodge = QRandomGenerator::global()->generate() % 100 < mLucky;
    if(canDodge){
        dodge();
        return;
    }

    const qreal hurt = qMax(power - mDefensivePower, (qreal)0);
    mHealth -= hurt;
    mCharItem->takeDamage(hurt);
    mTakeDamageSound->play();

    if(mHealth <= 0){
        QTimer::singleShot(500, this, &GameCharacter::die);
    }
}

void GameCharacter::healed(const qreal power)
{
    if(mHealth <= 0) return;
    mHealth += power;
    mCharItem->healed(power);
    mHealedSound->play();
}

void GameCharacter::moveTo(const QPoint newPos)
{
    if(mHealth <= 0) return;
    const QPoint dest = {newPos.x() * 64, newPos.y() * 64};
    mPos = newPos;
    mCharItem->moveTo(dest);
}

void GameCharacter::setPos(const QPoint newPos)
{
    const QPoint dest = {newPos.x() * 64, newPos.y() * 64};
    mCharItem->setTowards(newPos.x() > mPos.x());
    mPos = newPos;
    mCharItem->setPos(dest);
}

void GameCharacter::die()
{
    this->mCharItem->death();
}

void GameCharacter::dodge()
{
    if(mHealth <= 0) return;
    mCharItem->dodge();
}

void GameCharacter::setTowards(bool towardRight)
{
    mCharItem->setTowards(towardRight);
}

QVector<QPixmap> GameCharacter::requestIcons()
{
    QVector<QPixmap> rtn;
//    for(int i = 0;i < 5;i++){
//        rtn.append(R::IconPixmap->copy(32*i, 0, 32, 32));
//    }
    if(mRole == CharacterRole::Enemy){
        rtn.append(R::IconPixmap->copy(32*4, 0, 32, 32));
    }
    if(health() <= 0){
        rtn.append(R::IconPixmap->copy(0, 0, 32, 32));
    }
    if(speed() < mSpeed){
        rtn.append(R::IconPixmap->copy(416, 96, 32, 32));
    }
    if(defensivePower() > 0){
        rtn.append(R::IconPixmap->copy(32, 224, 32, 32));
    }
    return rtn;
}

void GameCharacter::setCharRole(const int role)
{
    mRole = role;
}

void GameCharacter::attack()
{
    if(mHealth <= 0) return;
    mCharItem->attack();
    mSwordSound->play();
}

//void GameCharacter::selected(bool slt)
//{

//}

void GameCharacter::click(GameCharItem *src)
{
    Q_UNUSED(src);
    if(charRole() == CharacterRole::Enemy){
        mEnemySound->play();
    }else if(charRole() == CharacterRole::Player1){
        mFriendSound->play();
    }
    emit clicked(this);
}

AttackAct *GameCharacter::attackAct() const
{
    return mAttackAct;
}

MoveAct *GameCharacter::moveAct() const
{
    return mMoveAct;
}

qreal GameCharacter::attackPower() const
{
    return mAttackPower;
}

void GameCharacter::setAttackPower(qreal newAttackPower)
{
    mAttackPower = newAttackPower;
}

void GameCharacter::setHealth(qreal newHealth)
{
    mHealth = newHealth;
}

void GameCharacter::setSpeed(qreal newSpeed)
{
    mSpeed = newSpeed;
}

void GameCharacter::setDefensivePower(qreal newDefensivePower)
{
    mDefensivePower = newDefensivePower;
}

void GameCharacter::setLucky(qreal newLucky)
{
    mLucky = newLucky;
}

qreal GameCharacter::health() const
{
    return mHealth;
}

qreal GameCharacter::speed() const
{
    const auto p = pos();
    if(game()->cellAt(p)->cellType() == LevelCellItem::CellType::Stone){
        return mSpeed * 0.6;
    }
    return mSpeed;
}

qreal GameCharacter::defensivePower() const
{
    return mDefensivePower;
}

qreal GameCharacter::lucky() const
{
    return mLucky;
}

GameScene *GameCharacter::game() const
{
    return mGame;
}

void GameCharacter::endTurn()
{
    mAttackAct->reset();
    mMoveAct->reset();

    const static int dirX[] = {0, 1, 0, -1};
    const static int dirY[] = {1, 0, -1, 0};

    const auto p = pos();
    int totHeal = 0;
    int totHurt = 0;
    for(int i = 0;i < 4;i++){
        const QPoint sp{p.x()+dirX[i], p.y()+dirY[i]};
        //qDebug()<<sp;
        if(!game()->validGamePos(sp)) continue;
        auto prop = game()->propAt(sp);
        if(prop == nullptr) continue;
        if(prop->propType() == GameProp::PropType::Magic){
            totHeal += 5;
        }
        if(prop->propType() == GameProp::PropType::Vase){
            totHurt += 5;
        }
    }
    if(totHeal > 0){
        healed(totHeal);
    }
    if(totHurt){
        attacked(totHurt);
    }
}

void GameCharacter::initDefaultAction()
{
    mMoveAct = new MoveAct(this, this);
    mAttackAct = new AttackAct(this, this);
}

QVector<GameCharAction *> GameCharacter::requestActionMenu()
{
    if(mHealth <= 0) return {};
    return {mMoveAct, mAttackAct};
}

const QString &GameCharacter::name() const
{
    return mName;
}

void GameCharacter::setName(const QString &newName)
{
    mName = newName;
}

GameCharItem *GameCharacter::charItem() const
{
    return mCharItem;
}
