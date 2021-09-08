#include "HelloScene.h"
#include "FirstScene.h"
#include "model/HUD.h"
#include "model/GameProp.h"
#include "item/MeowKnightItem.h"
#include "item/hud/ButtonItem.h"
#include "R.h"

#include <QtWidgets>

HelloScene::HelloScene(QObject *parent) : GameScene(parent)
{

}


void HelloScene::initHUD()
{
    GameScene::initHUD();
    setAllowOpenHUD(false);
    hud->toggleHUD();
}


void HelloScene::initChore()
{
    auto logoText = new QGraphicsTextItem();
    logoText->setPlainText("~~ M e o W ~~");
    QFont f;
    f.setBold(true);
    f.setFamily("Microsoft YaHei UI");
    f.setPointSize(50);
    logoText->setFont(f);
    logoText->setPos(250, 290);
    logoText->setZValue(3200);
    //qDebug() << "logo at " << logoText->boundingRect();
    addItem(logoText);
    logoText->setParent(this);

    auto logoMeow = new MeowKnightItem("grey");
    logoMeow->setPos(390, 30);
    logoMeow->setScale(14);
    logoMeow->setZValue(3200);
    addItem(logoMeow);
    logoMeow->setParent(this);

    auto b1 = new ButtonItem();
    b1->setBckPixmap(R::BtnPixmap->copy(133, 0, 130, 50));
    b1->setText("第一关");
    b1->setColor(Qt::white);
    b1->setFontPoint(24);
    b1->setPos(200, 460);

    auto b2 = new ButtonItem();
    b2->setBckPixmap(R::BtnPixmap->copy(133, 0, 130, 50));
    b2->setText("第二关");
    b2->setColor(Qt::white);
    b2->setFontPoint(24);
    b2->setPos(200 + 247, 460);

    auto b3 = new ButtonItem();
    b3->setBckPixmap(R::BtnPixmap->copy(133, 0, 130, 50));
    b3->setText("第三关");
    b3->setColor(Qt::white);
    b3->setFontPoint(24);
    b3->setPos(200 + 247 * 2, 460);

    addItem(b1);
    addItem(b2);
    addItem(b3);
    // 这里连接到各个对应关卡
    connect(b1, &ButtonItem::clicked, this, [this](){
        auto view = this->views()[0];
        auto first = new FirstScene();
        first->init();
        view->setScene(first);
        this->deleteLater();
    });

    auto m1 = new MeowKnightItem("grey");
    const int mscale = 5;
    m1->playAnimation(MeowKnightItem::AnimationName::Run);
    auto m2 = new MeowKnightItem("grey");
    m2->playAnimation(MeowKnightItem::AnimationName::Attack);
    auto m3 = new MeowKnightItem("grey");
    m3->playAnimation(MeowKnightItem::AnimationName::Dodge);
    auto m4 = new MeowKnightItem("grey");
    m4->playAnimation(MeowKnightItem::AnimationName::Jump);
    auto m5 = new MeowKnightItem("grey");
    m5->playAnimation(MeowKnightItem::AnimationName::AttackWithSkill);
    auto m6 = new MeowKnightItem("grey");
    m6->playAnimation(MeowKnightItem::AnimationName::TakeDamage);
    auto m7 = new MeowKnightItem("grey");
    m7->playAnimation(MeowKnightItem::AnimationName::Death);

    QVector<MeowKnightItem*> marr {m1, m2, m3, m4, m5, m6, m7};
    const int mmargin = 150;
    const int mbet = (1024 - mmargin * 2 - marr.size() * mscale * 32) / marr.size() + mscale * 32;
    for(int i = 0;i < marr.size();i++){
        marr[i]->setScale(mscale);
        marr[i]->setZValue(3200);
        marr[i]->setAutoStop(false);
        marr[i]->setPos(mmargin+mbet*i, 600);
        addItem(marr[i]);
        marr[i]->setParent(this);
    }
}

void HelloScene::initLevel()
{
    mLevel = new Level();
    mLevel->initLevel(GameWidth, GameHeight);
    mLevel->setScene(this);
}


void HelloScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << event->scenePos();
    GameScene::mouseReleaseEvent(event);
}


void HelloScene::initPropItems()
{
    auto magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({2, 4});
    addProp(magicProp);

    magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({13, 4});
    addProp(magicProp);
}
