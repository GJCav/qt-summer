#include "ThirdScene.h"
#include "model/GameProp.h"
#include "item/TextBoxItem.h"
#include "model/special/AthleteMeow.h"
#include "model/special/OrangeMeow.h"
#include "model/special/DoctorMeow.h"
#include "model/HUD.h"

ThirdScene::ThirdScene(QObject *parent) : GameScene(parent)
{

}


void ThirdScene::initLevel()
{
    GameScene::initLevel();
    mLevel->setStonePath(QRect{4, 2, 9, 1});
    mLevel->setStonePath(QRect{4, 9, 9, 1});

    mLevel->setStonePath(QRect{3, 3, 1, 1});
    mLevel->setStonePath(QRect{13, 3, 1, 1});
    mLevel->setStonePath(QRect{3, 8, 1, 1});
    mLevel->setStonePath(QRect{13, 8, 1, 1});

    mLevel->setStonePath(QRect{2, 4, 1, 4});
    mLevel->setStonePath(QRect{14, 4, 1, 4});
}

void ThirdScene::initPropItems()
{
    auto magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({4, 1});
    addProp(magicProp);

    magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({12, 1});
    addProp(magicProp);

    for(int y = 4;y <= 5;y++){
        for(int x = 5;x <= 6;x++){
            auto c = new GameProp(this, GameProp::PropType::Chest);
            c->setPos({x, y});
            addProp(c);
        }
        for(int x = 10;x <= 11;x++){
            auto c = new GameProp(this, GameProp::PropType::Chest);
            c->setPos({x, y});
            addProp(c);
        }
    }

    for(int x = 7;x <= 9;x++){
        auto v = new GameProp(this, GameProp::PropType::Vase);
        v->setPos({x, 6});
        addProp(v);
    }
    auto v = new GameProp(this, GameProp::PropType::Vase);
    v->setPos({8, 7});
    addProp(v);

    // add stones
    for(int x = 5;x <= 6;x++){
        auto s = new GameProp(this, GameProp::PropType::Stone);
        s->setPos({x, 2});
        addProp(s);
    }
    for(int x = 10;x <= 11;x++){
        auto s = new GameProp(this, GameProp::PropType::Stone);
        s->setPos({x, 2});
        addProp(s);
    }
    for(int x = 6;x <= 10;x++){
        auto s = new GameProp(this, GameProp::PropType::Stone);
        s->setPos({x, 9});
        addProp(s);
    }
    for(int y = 4;y <= 7;y++){
        auto s = new GameProp(this, GameProp::PropType::Stone);
        s->setPos({2, y});
        addProp(s);
        s = new GameProp(this, GameProp::PropType::Stone);
        s->setPos({14, y});
        addProp(s);
    }
}

void ThirdScene::initChars()
{
    for(int y = 5;y <= 6;y++){
        GameCharacter* p = createPlayerChar<AthleteMeow>();
        addChar(p);
        p->setPos({1, y});
        p = createPlayerChar<OrangeMeow>();
        addChar(p);
        p->setPos({3, y});

        auto e = createEnemyChar<OrangeMeow>();
        addChar(e);
        e->setPos({12, y});
        e->setTowards(false);
    }

    for(int y = 3;y <= 8;y++){
        auto e = createEnemyChar<GameCharacter>();
        addChar(e);
        e->setPos({13, y});
        e->setTowards(false);
    }

    for(int y = 6;y <= 8;y++){
        GameCharacter* p = createPlayerChar<GameCharacter>();
        p->setPos({6, y});
    }

    mDocMeow = createPlayerChar<DoctorMeow>();
    addChar(mDocMeow);
    mDocMeow->setPos({5, 7});

    mBossMeow = createEnemyChar<BossMeow>();
    addChar(mBossMeow);
    mBossMeow->setPos({8, 4});
    mBossMeow->setTowards(false);

}

void ThirdScene::initChore()
{
    this->hud->toggleHUD();

    TextBoxItem *box = new TextBoxItem();
    box->setFontPointSize(17);
    box->setSize(450, 300);
    box->setPos(200, 160);
    box->setVisible(false);
    box->setUseAnimation(true);
    box->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:100px; font-size: 50px\">第三关：庸医和Boss</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————不要轻易相信庸医；面对Boss最好速战速决</p>\
    <p style=\"margin-left:10px; \">敌方Boss出现了，怎么办？</p>\
    <p style=\"margin-left:10px; \">没关系，大橘和庸医加入了我们。</p>\
    <p style=\"margin-left:10px; \">你问什么是庸医？</p>\
    <p style=\"margin-left:10px; \">我只能说懂的都懂，不懂的说了也不懂</p>\
    <br>\
    <p style=\"margin-left:10px; \">胜利条件：Boss死亡</p>\
    <p style=\"margin-left:10px; \">失败条件：庸医死亡</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————再怎么说也是个医生 →_→</p>\
    </body></html>");
    addItem(box);

    connect(box, &TextBoxItem::clicked, box, &TextBoxItem::close);

    box->show();
}


int ThirdScene::successOrFailed()
{
    if(mDocMeow->health() <= 0) return 2;
    if(mBossMeow->health() <= 0) return 1;
    return 0;
}
