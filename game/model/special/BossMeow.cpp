#include "BossMeow.h"
#include "item/MeowKnightItem.h"
#include "model/Level.h"
#include "model/GameScene.h"

BossMeow::BossMeow(GameScene *game)
    : BossMeow(new MeowKnightItem("yellow"), game, GameCharacter::CharacterRole::Enemy)
{

}

BossMeow::BossMeow(GameCharItem *item, GameScene *game, int role)
    : GameCharacter(item, game, role)
{
    setName("Boss 喵~");
    setHealth(100);
    setDefensivePower(2);
    setAttackPower(10);
    setSpeed(5);
}


void BossMeow::endTurn()
{
    GameCharacter::endTurn();
    if(health() > 0){
        mTurnCount++;
        mTurnCount %= 4;
        if(mTurnCount == 0){
            QPoint find(-1, -1);
            for(int i = 1;i <= 2;i++){
                for(int dx = -i;dx <= i;dx++){
                    int dy = qAbs(i - qAbs(i));

                    QPoint p(pos().x()+dx, pos().y()+dy);
                    if(
                        game()->validGamePos(p) &&
                        game()->propAt(p) == nullptr &&
                        game()->charAt(p) == nullptr &&
                        game()->level()->canPlaceGameModel(p))
                    {
                        find = p;
                        break;
                    }

                    dy = -dy;
                    p = QPoint(pos().x()+dx, pos().y()+dy);
                    if(
                        game()->validGamePos(p) &&
                        game()->propAt(p) == nullptr &&
                        game()->charAt(p) == nullptr &&
                        game()->level()->canPlaceGameModel(p))
                    {
                        find = p;
                        break;
                    }
                }
                if(find.x() != -1) break;
            }
            if(find.x() != -1){
                MeowKnightItem *meow = new MeowKnightItem("yellow");
                GameCharacter *ch = new GameCharacter(meow, game(), GameCharacter::CharacterRole::Enemy);
                game()->addChar(ch);
                ch->setPos(find);
                ch->setTowards(false);
            }
        }
    }
}
