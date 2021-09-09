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
        if(!actions[i]->isEnabled()) continue;
        auto btn = new ButtonItem(mActBtnGroup);

        //qDebug() << "create action button: " << actions[i]->text() << ", " << actions[i];
        //qDebug() << "       action button at: " << btn;

        btn->setBckPixmap(R::BtnPixmap->copy(133, 0, 130, 50));
        btn->setText(actions[i]->text());
        btn->setColor(Qt::white);
        btn->setFontPoint(24);
        btn->setY((ActBtnHeight + ActBtnGap) * i);

        connect(btn, &ButtonItem::clicked, actions[i], &QAction::trigger);

        actions[i]->setButtonItem(btn);
    }
    mActBtnGroup->setZValue(ZValue);
    mActBtnGroup->setPos(ActBtnPos);
    mActBtnGroup->setGraphicsEffect(createShadow());

    mGame->addItem(mActBtnGroup);
}

void HUD::setStatusName(const QString &s) {mStatusName->setPlainText(s);}

void HUD::setStatusHealth(const QString &s) {mStatusHealth->setPlainText(s);}

void HUD::setStatusSpeed(const QString &s) {mStatusSpeed->setPlainText(s);}

void HUD::setStatusDefensive(const QString &s){mStatusDefensive->setPlainText(s);}

void HUD::setStatusLucky(const QString &s) {mStatusLucky->setPlainText(s);}

void HUD::setStatusAttack(const QString &s) {mStatusAttack->setPlainText(s);}

void HUD::setStatusName(int n) {setStatusName(QString::number(n));}

void HUD::setStatusHealth(int n) {setStatusHealth(QString::number(n));}

void HUD::setStatusSpeed(int n) {setStatusSpeed(QString::number(n));}

void HUD::setStatusDefensive(int n) {setStatusDefensive(QString::number(n));}

void HUD::setStatusLucky(int n) { setStatusLucky(QString::number(n));}

void HUD::setStatusAttack(int n) { setStatusAttack(QString::number(n));}

void HUD::toggleHUD()
{
    //R::Sound::ToggleHUD->play();
    mToggleHUDSound->play();
    if(mVisible){
        mTitleProxy->setVisible(false);
        mIconGroup->setVisible(false);
        mActBtnGroup->setVisible(false);
        mStatusProxy->setVisible(false);
        mEndTurnBtn->setVisible(false);
        mVisible = false;
    }else{
        mTitleProxy->setVisible(true);
        mIconGroup->setVisible(true);
        mActBtnGroup->setVisible(true);
        mStatusProxy->setVisible(true);
        mEndTurnBtn->setVisible(true);
        mVisible = true;
    }
}

bool HUD::allowEndTurn() const
{
    return mAllowEndTurn;
}

void HUD::setAllowEndTurn(bool newAllowEndTurn)
{
    if(mAllowEndTurn == newAllowEndTurn) return;
    mAllowEndTurn = newAllowEndTurn;
    mEndTurnBtn->setEnabled(mAllowEndTurn);
}

void HUD::initHud()
{
    mToggleHUDSound = new QSoundEffect(this);
    mToggleHUDSound->setSource(QUrl("qrc:/asset/sound/openhud.wav"));

    mActBtnGroup = new QGraphicsItemGroup();
    mGame->addItem(mActBtnGroup);

    mIconGroup = new QGraphicsItemGroup();
    mGame->addItem(mIconGroup);

    initTitleBar();
    initStatusPanel();
    initNextTurnBtn();
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
    mTitleLabel->setText("-/-");

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

    mStatusName->setPlainText("-/-");
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
        item->setPlainText("-/-");
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
        item->setPlainText("-/-");
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

void HUD::initNextTurnBtn()
{
    mEndTurnBtn = new ButtonItem();
    mEndTurnBtn->setBckPixmap(R::BtnPixmap->copy(0, 55, 163, 62));
    mEndTurnBtn->setText("回合结束");
    mEndTurnBtn->setFontPoint(23);
    mEndTurnBtn->setColor(Qt::white);
    mEndTurnBtn->setPos(800, 670);
    mEndTurnBtn->setGraphicsEffect(createShadow(5, 5, 20));

    mGame->addItem(mEndTurnBtn);

    connect(mEndTurnBtn, &ButtonItem::clicked, this, [this](){
        emit clickedEndTurn();
        setIcons({});
        setActBtns({});
        if(mVisible) toggleHUD();
    });

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
        //qDebug() << "remove hud item: " << list[i];

        mGame->removeItem(list[i]);
        delete list[i];
    }
}
