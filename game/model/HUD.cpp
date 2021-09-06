#include "HUD.h"
#include "item/hud/ButtonItem.h"
#include "R.h"
#include <QtGui>
#include <QtWidgets>

HUD::HUD(QGraphicsScene *scene, QObject *parent)
    : QObject(parent)
{
    mScene = scene;
    initHud();
}

HUD::~HUD()
{
}

void HUD::setIcons(const QVector<QPixmap>& iconPixmaps)
{
    if(mIconGroup != nullptr)
        mScene->destroyItemGroup(mIconGroup);
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
        mIconGroup->addToGroup(icon);
    }

    mIconGroup->setZValue(ZValue);
    mScene->addItem(mIconGroup);
}

void HUD::setActBtns(const QVector<QAction *>& actions)
{
    if(mActBtnGroup != nullptr){
        mScene->destroyItemGroup(mActBtnGroup);
    }

    mActBtnGroup = new QGraphicsItemGroup;
    mActBtnGroup->setHandlesChildEvents(false);
    for(int i = 0;i < actions.size();i++){
        auto btn = new ButtonItem(mActBtnGroup);
        btn->setBckPixmap(R::BtnPixmap->copy(0, 0, 130, 50));
        btn->setText(actions[i]->text());
        btn->setFontPoint(24);
        btn->setY((ActBtnHeight + ActBtnGap) * i);

        mActBtnGroup->addToGroup(btn);
        connect(btn, &ButtonItem::clicked, actions[i], &QAction::trigger);
    }
    mActBtnGroup->setZValue(ZValue);
    mScene->addItem(mActBtnGroup);
    mActBtnGroup->setPos(ActBtnPos);
}

void HUD::initHud()
{
    initTitleBar();
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

    titleLabel = new QLabel();
    titleLabel->setText("标题栏");

    lyt->addWidget(titleLabel);


    mTitleProxy = new QGraphicsProxyWidget();
    mTitleProxy->setWidget(mTitlePanel);
    mTitleProxy->setPos(-20, 30);
    mTitleProxy->setZValue(ZValue);

    mScene->addItem(mTitleProxy);
}
