#include "FirstScene.h"
#include "model/GameProp.h"
#include "item/TextBoxItem.h"
#include "model/HUD.h"

FirstScene::FirstScene(QObject *parent) : GameScene(parent)
{

}


void FirstScene::initLevel()
{
    GameScene::initLevel();
    mLevel->setStonePath(QRect{6, 1, 3, 10});
}

void FirstScene::initPropItems()
{
    auto magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({5, 2});
    addProp(magicProp);

    magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({9, 2});
    addProp(magicProp);

    magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({1, 8});
    addProp(magicProp);

    magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({13, 8});
    addProp(magicProp);
}

void FirstScene::initChars()
{
    auto ch = createPlayerChar<GameCharacter>();
    addChar(ch);
    ch->setPos({4, 3});

    ch = createPlayerChar<GameCharacter>();
    addChar(ch);
    ch->setPos({4, 8});

    ch = createEnemyChar<GameCharacter>();
    ch->setPos({10, 3});
    ch->setTowards(false);
    addChar(ch);

    ch = createEnemyChar<GameCharacter>();
    ch->setPos({10, 8});
    ch->setTowards(false);
    addChar(ch);
}

void FirstScene::initChore()
{
    this->hud->toggleHUD();

    TextBoxItem *boxStory = new TextBoxItem();
    boxStory->setFontPointSize(24);
    boxStory->setSize(450, 300);
    boxStory->setPos(200, 160);
    boxStory->setVisible(false);
    boxStory->setHtml("<div style=\"margin-left: 40px; margin-top: 40px\">\
    <br>\
    很久很久以前~~ <br>\
    喵星人突然出现，<br>\
    。。。<br>\
    <br>\
    <br>\
    咳咳，编不下去了<br>\
    干就完了\
    </div>");
    addItem(boxStory);

    TextBoxItem *boxHelp = new TextBoxItem();
    boxHelp->setFontPointSize(20);
    boxHelp->setSize(450, 300);
    boxHelp->setPos(200, 160);
    boxHelp->setVisible(false);
    boxHelp->setHtml("<div style=\"margin-left: 40px;\"><br>\
    看起来你是个新手？来个教程吧：<br>\
    按<italic><strong>H</strong></italic>打开/关闭HUD<br>\
    用鼠标操作猫猫<br>\
    左上角是名称栏，<br>\
    名称栏右侧有图标表示特殊属性，<br><br>\
    其余的看一眼就会啦~~<br>\
    </div>");
    addItem(boxHelp);

    TextBoxItem *box = new TextBoxItem();
    box->setFontPointSize(20);
    box->setSize(450, 300);
    box->setPos(200, 160);
    box->setVisible(false);
    box->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:100px; font-size: 50px\">第一关：菜鸡互啄</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————不会吧，不会吧，不会第一关就过不了吧</p>\
    <p style=\"margin-left:10px; \">邪恶的猫猫要来抢走喵喵的铲屎官，<br>\
    你可爱的主子们当然不会同意，<br>\
    它们为了保护你挺身而出，但也需要你的支援。<br><br>\
    作为喵喵的铲屎官，请指挥它们迎来胜利吧。</p>\
    </body></html>");
    addItem(box);

    txtBoxSeries({boxStory, boxHelp, box});
    boxStory->show();
}


















