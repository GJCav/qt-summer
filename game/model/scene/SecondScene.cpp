#include "SecondScene.h"
#include "model/GameProp.h"
#include "item/TextBoxItem.h"
#include "model/special/AthleteMeow.h"
#include "model/special/OrangeMeow.h"
#include "model/HUD.h"

SecondScene::SecondScene(QObject *parent) : GameScene(parent)
{

}


void SecondScene::initLevel()
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

void SecondScene::initPropItems()
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
}

void SecondScene::initChars()
{
    for(int y = 6;y <= 7;y++){
        auto ch = createPlayerChar<AthleteMeow>();
        addChar(ch);
        ch->setPos({4, y});

        auto ach = createPlayerChar<GameCharacter>();
        addChar(ach);
        ach->setPos({5, y});

        auto a = createEnemyChar<GameCharacter>();
        addChar(a);
        a->setPos({11, y});
        a->setTowards(false);

        a = createEnemyChar<OrangeMeow>();
        addChar(a);
        a->setPos({12, y});
        a->setTowards(false);
    }
}

void SecondScene::initChore()
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
    <p style=\"margin-left:100px; font-size: 50px\">第二关：大橘为重</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————十个橘猫九个胖，还有一个特别胖</p>\
    <p style=\"margin-left:10px; \">敌方出动的大橘，更是重量级猫猫</p>\
    <p style=\"margin-left:10px; \">我们不甘示弱，派出了运动员猫猫。</p>\
    <p style=\"margin-left:10px; \">请你展示：四两拨千斤，讲究个化劲儿~~</p><br>\
    <p style=\"margin-left:10px; \">温馨提示a：小心花瓶。</p>\
    <p style=\"margin-left:10px; \">温馨提示b：运动员猫猫需要一小段助跑。</p>\
    </body></html>");
    addItem(box);

    connect(box, &TextBoxItem::clicked, box, &TextBoxItem::close);

    box->show();
}
