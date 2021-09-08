#include "BaseAI.h"
#include "model/GameCharacter.h"
#include "model/action/AttackAct.h"
#include "model/action/MoveAct.h"
#include <tuple>

namespace  {
using CharRole = GameCharacter::CharacterRole;
using MoveDestType = GameScene::MoveDestType;
using ReachCharType = GameScene::ReachCharType;
using std::get;

int mdis(QPoint a, QPoint b){
    return qAbs(a.x()-b.x()) + qAbs(a.y()-b.y());
}

qreal odis(QPoint a, QPoint b){
    return qSqrt((a.x()-b.x())*(a.x()-b.x())+(a.y()-b.y())*(a.y()-b.y()));
}

}

BaseAI::BaseAI(GameScene *game)
    : EnemyAI(game)
{

}

void BaseAI::nextAction()
{
    if(stage == 0){ // init
        enemies.clear();
        auto chs = game()->chars();
        for(int i = 0;i < chs.size();i++){
            if(chs[i]->charRole() == CharRole::Enemy)
                enemies.append(chs[i]);
        }
        acted.fill(false, enemies.size());
        stage = 1;

        QTimer::singleShot(0, this, &BaseAI::nextAction);
    }else if(stage == 1){ // perform action
        GameCharacter *enemy = nullptr;
        for(int i = 0;i < acted.size();i++){
            if(acted[i])continue;
            acted[i] = true;
            if(enemies[i]->health() <= 0) continue;;
            enemy = enemies[i];
            break;
        }

        if(enemy == nullptr){ // all action finished
            stage = 2;
            QTimer::singleShot(0, this, &BaseAI::nextAction);
            return;
        }

        bool doAttack = tryAttack(enemy);
        if(!doAttack){
            bool doMove = tryMove(enemy);
            if(doMove){ // need another attack try
                stage = 3;
            }else{ // can't move, so consider next enemy
                QTimer::singleShot(0, this, &BaseAI::nextAction);
            }
        }

    }else if(stage == 2){ // end ai
        stage = 0;
        emit AITurnFinished();
    }else if(stage == 3){ // first move and try attack again
        bool doAttack = tryAttack(moreTryEnemy);
        moreTryEnemy = nullptr;

        stage = 1;
        if(!doAttack){ // again cant attack, so consider next enemy

            QTimer::singleShot(0, this, &BaseAI::nextAction);
        }
    }
}

void BaseAI::start()
{
    nextAction();
}

bool BaseAI::tryAttack(GameCharacter* enemy)
{
    auto charList = game()->listReachableCharacterPos(
        enemy->pos(),
        enemy->attackAct()->attackRangeMax(),
        enemy->attackAct()->attackRangeMin()
    );
    GameCharacter* attackTgt = nullptr;
    for(int i = 0;i < charList.size();i++){
        if(get<1>(charList[i]) != ReachCharType::Valid) continue;
        auto c = game()->charAt(get<0>(charList[i]));
        if(c->charRole() != CharRole::Player1) continue;
        if(c->health() <= 0) continue;
        attackTgt = c;
    }
    if(attackTgt != nullptr){
        enemy->attack();
        QTimer::singleShot(200, this, [this, attackTgt, enemy](){
            attackTgt->attacked(enemy->attackPower());
            QTimer::singleShot(500, this, &BaseAI::nextAction);
        });

        return true;
    }
    return false;
}

bool BaseAI::tryMove(GameCharacter *enemy)
{
    // find closest player
    auto chs = game()->chars();
    GameCharacter* player = nullptr;
    int md = -1;
    qreal od = -1;
    for(int i = 0;i < chs.size();i++){
        auto c = chs[i];
        if(c->charRole() != CharRole::Player1) continue;
        if(c->health() <= 0) continue;

        auto newmd = mdis(enemy->pos(), c->pos());
        auto newod = odis(enemy->pos(), c->pos());

        auto update = [&](){
            player = c;
            md = newmd;
            od = newod;
        };

        if(md == -1){
            update();
        }else if(newmd < md){
            update();
        }else if(newmd == md && newod < od){
            update();
        }
    }

    // find a place closest to player
    auto dstList = game()->listMoveDestination(
        enemy->pos(),
        enemy->moveAct()->getSpeedMax(),
        enemy->moveAct()->getSpeedMin()
    );
    QPoint dst;
    md = -1;
    od = -1;
    for(int i = 0;i < dstList.size();i++){
        if(get<1>(dstList[i]) != MoveDestType::Valid) continue;
        QPoint p = get<0>(dstList[i]);

        auto newmd = mdis(player->pos(), p);
        auto newod = odis(player->pos(), p);

        auto update = [&](){
            dst = p;
            md = newmd;
            od = newod;
        };

        if(md == -1){
            update();
        }else if(newmd < md){
            update();
        }else if(newmd == md && newod < od){
            update();
        }
    }

    if(md == -1){
        return false;
    }

    enemy->moveTo(dst);
    moreTryEnemy = enemy;
    QTimer::singleShot(900, this, &BaseAI::nextAction);

    return true;
}





















