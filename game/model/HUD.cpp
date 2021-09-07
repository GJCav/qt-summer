#include "HUD.h"
#include "item/hud/ButtonItem.h"
#include "R.h"
#include "ui/DarkPanel.h"
#include <QtGui>
#include <QtWidgets>

HUD::HUD(GameScene *scene)
    : QObject(scene)
{
    mGame = scene;
    initHud();
}

HUD::~HUD()
{
}

void HUD::setIcons(const QVector<QPixmap>& iconPixmaps)
{
    deleteItemGroup(mIconGroup);
    mIcons.clear();

    mIconPixmaps = iconPixmaps;
    mIconGroup = new QGraphicsItemGroup();
    for(int i = 0;i < mIconPixmaps.size();i++){
        auto icon = new IconItem(mIconGroup);
        const auto& pix = mIconPixmaps.at(i);
        icon->setPixmap(pix.scaled(IconSize, IconSize));
        icon->setPos({
            (qreal)IconPos.x() + (IconGap + IconSize) * i,
            IconPos.y()
        });

        mIcons.append(icon);
    }
    mIconGroup->setZValue(ZValue);
    mIconGroup->setGraphicsEffect(createShadow());

    mGame->addItem(mIconGroup);
}

void HUD::setActBtns(const QVector<GameCharAction *>& actions)
{
    deleteItemGroup(mActBtnGroup);

    mActBtnGroup = new QGraphicsItemGroup;
    mActBtnGroup->setHandlesChildEvents(false);
    for(int i = 0;i < actions.size();i++){
        auto btn = new ButtonItem(mActBtnGroup);

        btn->setBckPixmap(R::BtnPixmap->copy(133, 0, 130, 50));
        btn->setText(actions[i]->text());
        btn->setColor(Qt::white);
        btn->setFontPoint(24);
        btn->setY((ActBtnHeight + ActBtnGap) * i);

        connect(btn, &ButtonItem::clicked, actions[i], &QAction::trigger);
    }
    mActBtnGroup->setZValue(ZValue);
    mActBtnGroup->setPos(ActBtnPos);
    mActBtnGroup->setGraphicsEffect(createShadow());

    mGame->addItem(mActBtnGroup);
}

void HUD::toggleHUD()
{
    if(mVisible){
        mTitleProxy->setVisible(false);
        mIconGroup->setVisible(false);
        mActBtnGroup->setVisible(false);
        mStatusProxy->setVisible(false);
        mVisible = false;
    }else{
        mTitleProxy->setVisible(true);
        mIconGroup->setVisible(true);
        mActBtnGroup->setVisible(true);
        mStatusProxy->setVisible(true);
        mVisible = true;
    }
}

void HUD::initHud()
{
    mActBtnGroup = new QGraphicsItemGroup();
    mGame->addItem(mActBtnGroup);

    mIconGroup = new QGraphicsItemGroup();
    mGame->addItem(mIconGroup);

    initTitleBar();
    initStatusPanel();
}

void HUD::initTitleBar()
{
    mTitlePanel = new LightWoodPanel();
    mTitlePanel->setGeometry(0, 0, 320, 60);

    auto lyt = new QHBoxLayout();
    lyt->setContentsMargins(50, 9, 9, 9);
    mTitlePanel->setLayout(lyt);

    QFont font;
    font.setFamily("Microsoft YaHei UI");
    font.setPointSize(24);
    mTitlePanel->setFont(font);

    QPalette pal = mTitlePanel->palette();
    QColor c(0, 0, 0, 0);
    pal.setColor(QPalette::Window, c);
    mTitlePanel->setPalette(pal);

    mTitleLabel = new QLabel();
    mTitleLabel->setText("标题栏");

    lyt->addWidget(mTitleLabel);


    mTitleProxy = new QGraphicsProxyWidget();
    mTitleProxy->setWidget(mTitlePanel);
    mTitleProxy->setPos(-20, 30);
    mTitleProxy->setZValue(ZValue);
    mTitleProxy->setGraphicsEffect(createShadow());

    mGame->addItem(mTitleProxy);
}

void HUD::initStatusPanel()
{
    auto panel = new DarkPanel();
    panel->setGeometry(0, 0, 370, 250);

    QFont font;
    font.setFamily("Microsoft YaHei UI");
    font.setPointSize(19);
    font.setBold(true);
    panel->setFont(font);

    QPalette pal = panel->palette();
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 0));
    pal.setColor(QPalette::Base, QColor(0, 0, 0, 0));
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    panel->setPalette(pal);

//    mStatusName = new QLabel(panel);
//    mStatusName->setGeometry(30, 30, 120, 30);
//    font.setPointSize(22);
//    mStatusName->setFont(font);
//    mStatusName->setText("Name");
//    //mStatusName->setGraphicsEffect(createShadow(0, 3, 5));

    mStatusProxy = new QGraphicsProxyWidget();

    mStatusName = new QGraphicsTextItem(mStatusProxy);
    mStatusHealth = new QGraphicsTextItem(mStatusProxy);
    mStatusSpeed = new QGraphicsTextItem(mStatusProxy);
    mStatusDefensive = new QGraphicsTextItem(mStatusProxy);
    mStatusLucky = new QGraphicsTextItem(mStatusProxy);
    mStatusAttack = new QGraphicsTextItem(mStatusProxy);

    mStatusName->setPlainText("Name");
    mStatusName->setPos(30, 30);
    mStatusName->setFont(font);
    mStatusName->setDefaultTextColor(Qt::white);
    mStatusName->setGraphicsEffect(createShadow(0, 3, 5));

    QVector<QGraphicsTextItem*> _arr = {
        mStatusHealth,
        mStatusSpeed,
        mStatusDefensive
    };
    for(int i = 0;i < _arr.size();i++){
        auto item = _arr[i];
        item->setPos(85, 75+40*i);
        item->setFont(font);
        item->setDefaultTextColor(Qt::white);
        item->setGraphicsEffect(createShadow(0, 3, 5));
        item->setPlainText("100");
    }

    _arr = {
        mStatusAttack,
        mStatusLucky,
    };
    for(int i = 0;i < _arr.size();i++){
        auto item = _arr[i];
        item->setPos(250, 75+40*i);
        item->setFont(font);
        item->setDefaultTextColor(Qt::white);
        item->setGraphicsEffect(createShadow(0, 3, 5));
        item->setPlainText("100");
    }

    const int gapY = 42;
    // health icon
    int curY = 75;
    auto icon = new QGraphicsPixmapItem(mStatusProxy);
    icon->setPixmap(R::IconPixmap->copy(192, 0, 32, 32));
    icon->setPos(50, curY);
    icon->setGraphicsEffect(createShadow(0, 3, 5));
    curY += gapY;

    // speed icon
    icon = new QGraphicsPixmapItem(mStatusProxy);
    icon->setPixmap(R::IconPixmap->copy(64, 256, 32, 32));
    icon->setPos(50, curY);
    icon->setGraphicsEffect(createShadow(0, 3, 5));
    curY += gapY;

    // defensice icon
    icon = new QGraphicsPixmapItem(mStatusProxy);
    icon->setPixmap(R::IconPixmap->copy(224, 224, 32, 32));
    icon->setPos(50, curY);
    icon->setGraphicsEffect(createShadow(0, 3, 5));
    //curY += gapY;

    // attack icon
    curY = 75;
    icon = new QGraphicsPixmapItem(mStatusProxy);
    icon->setPixmap(R::IconPixmap->copy(288, 160, 32, 32));
    icon->setPos(215, curY);
    icon->setGraphicsEffect(createShadow(0, 3, 5));
    curY += gapY;

    // lucky icon
    icon = new QGraphicsPixmapItem(mStatusProxy);
    icon->setPixmap(R::IconPixmap->copy(96, 576, 32, 32));
    icon->setPos(215, curY);
    icon->setGraphicsEffect(createShadow(0, 3, 5));

    mStatusHealth->setDefaultTextColor(QColor("#aaff7f"));
    mStatusSpeed->setDefaultTextColor(QColor("#aaaa7f"));
    mStatusDefensive->setDefaultTextColor(QColor("#8792b1"));
    mStatusAttack->setDefaultTextColor(QColor("#f06277"));
    mStatusLucky->setDefaultTextColor(QColor("#ffbf36"));


    mStatusProxy->setWidget(panel);
    mStatusProxy->setPos(10, 510);
    mStatusProxy->setZValue(ZValue);
    mStatusProxy->setGraphicsEffect(createShadow());

    mGame->addItem(mStatusProxy);
}

QGraphicsDropShadowEffect *HUD::createShadow(int offsetX, int offsetY, int blur)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(offsetX, offsetY);
    shadow->setColor(QColor(0, 0, 0, 128));
    shadow->setBlurRadius(blur);
    return shadow;
}

void HUD::deleteItemGroup(QGraphicsItemGroup* group)
{
    if(group == nullptr) return;
    auto list = group->childItems();
    mGame->destroyItemGroup(group);
    for(int i = 0;i < list.size();i++){
        mGame->removeItem(list[i]);
        delete list[i];
    }
}
