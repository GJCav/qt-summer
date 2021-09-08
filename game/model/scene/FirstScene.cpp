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
    boxStory->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:10px; margin-top:20px;\">很久很久以前~~</p>\
    <p style=\"margin-left:10px; \">喵星人突然出现，</p>\
    <p style=\"margin-left:10px; \">。</p>\
    <p style=\"margin-left:10px; \">。。</p>\
    <p style=\"margin-left:10px; \">。。。</p>\
    <p style=\"margin-left:10px; \">咳咳，编不下去了</p>\
    <p style=\"margin-left:10px; \">干就完了</p>\
    </body></html>");
    addItem(boxStory);

    TextBoxItem *boxHelp = new TextBoxItem();
    boxHelp->setFontPointSize(17);
    boxHelp->setSize(450, 300);
    boxHelp->setPos(200, 160);
    boxHelp->setVisible(false);
    boxHelp->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:100px; font-size: 50px\">前言：简单教程</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————跳过了新手教程的玩家.jpg</p>\
    <p style=\"margin-left:10px; \">看起来你是个新手？来个教程吧：</p>\
    <p style=\"margin-left:10px; \">按<italic><strong>H</strong></italic>打开/关闭HUD。</p>\
    <p style=\"margin-left:10px; \">用鼠标操作猫猫</p>\
    <p style=\"margin-left:10px; \">左上角是名称栏，名称栏右侧有图标表示特殊属性。</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————看了又不吃亏系列</p>\
    <p style=\"margin-left:10px; \">按<italic><strong>ESC</strong></italic>取消操作</p>\
    </body></html>");
    addItem(boxHelp);

    TextBoxItem *box = new TextBoxItem();
    box->setFontPointSize(17);
    box->setSize(450, 300);
    box->setPos(200, 160);
    box->setVisible(false);
    box->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:100px; font-size: 50px\">第一关：菜鸡互啄</p>\
    <p style=\"margin-left:80px; font-size: 20px\">————不会吧，不会吧，不会第一关就过不了吧</p>\
    <p style=\"margin-left:10px; \">邪恶的猫猫要来抢走喵喵的铲屎官，</p>\
    <p style=\"margin-left:10px; \">你可爱的主子们当然不会同意，</p>\
    <p style=\"margin-left:10px; \">它们为了保护你挺身而出，但也需要你的支援。</p>\
    <p style=\"margin-left:10px; \">作为喵喵的铲屎官，请指挥它们迎来胜利吧。</p><br>\
    <p style=\"margin-left:10px; \">哎？那根柱子是什么？要不要去看看？</p>\
    </body></html>");
    addItem(box);

    txtBoxSeries({boxStory, boxHelp, box});
    boxStory->show();
}


















