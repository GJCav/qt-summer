#ifndef HUD_H
#define HUD_H

#include "item/hud/IconItem.h"
#include "item/hud/ButtonItem.h"
#include "item/TextBoxItem.h"
#include "ui/LightWoodPanel.h"
#include "GameScene.h"
#include "model/GameCharAction.h"
#include "GameCharacter.h"
#include <QObject>
#include <QVector>
#include <QLabel>
#include <QGraphicsItemGroup>
#include <QGraphicsDropShadowEffect>
#include <QSoundEffect>

class HUD : public QObject
{
    Q_OBJECT
public:
    constexpr static int ZValue = 3200;
    constexpr static QPoint IconPos = {320, 40};
    constexpr static int IconSize = 40;
    constexpr static int IconGap = 10;
    constexpr static QPoint ActBtnPos = {830, 140};
    constexpr static int ActBtnHeight = 50;
    constexpr static int ActBtnGap = 10;

    HUD(GameScene *scene);
    ~HUD();

    inline void setTitle(const QString& s) {mTitleLabel->setText(s);}

    void setIcons(const QVector<QPixmap>& iconPixmaps);
    void setActBtns(const QVector<GameCharAction*>& actions);

    void toggleHUD();
    inline bool visible() const { return mVisible;}
    inline bool actActBtnVisible() const {return mActBtnVisible;}
    inline void toggleActBtn() {
        mActBtnVisible = !mActBtnVisible;
        mActBtnGroup->setVisible(mActBtnVisible & mVisible);
    };
    inline void setActBtnVisible(bool vis){
        mActBtnVisible = vis;
        mActBtnGroup->setVisible(mActBtnVisible & mVisible);
    }

    //ButtonItem *endTurnBtn() const;


    bool allowEndTurn() const;
    void setAllowEndTurn(bool newAllowEndTurn);
    inline bool endTurnVisible() {return mEndTurnBtn->isVisible();}
    inline void setEndTurnVisible(bool v) {mEndTurnBtn->setVisible(v);}

public slots:
    void setStatusName(const QString& s);
    void setStatusHealth(const QString& s);
    void setStatusSpeed(const QString& s);
    void setStatusDefensive(const QString& s);
    void setStatusLucky(const QString& s);
    void setStatusAttack(const QString& s);

    void setStatusName(int n);
    void setStatusHealth(int n);
    void setStatusSpeed(int n);
    void setStatusDefensive(int n);
    void setStatusLucky(int n);
    void setStatusAttack(int n);

signals:
    void clickedEndTurn();

private:
    bool mVisible = true;
    bool mActBtnVisible = true;

    GameScene *mGame;

    QGraphicsProxyWidget* mTitleProxy;
    LightWoodPanel* mTitlePanel;
    QLabel *mTitleLabel;
    //TextBoxItem *mInfoPanel; 写不动了，告辞


    QGraphicsItemGroup *mIconGroup = nullptr;
    QVector<QPixmap> mIconPixmaps;
    QVector<IconItem*> mIcons;

    QGraphicsItemGroup *mActBtnGroup = nullptr;
    //QVector<ButtonItem*> actionBtns;

    QGraphicsProxyWidget* mStatusProxy;
    QGraphicsTextItem* mStatusName;
    QGraphicsTextItem* mStatusHealth;
    QGraphicsTextItem* mStatusSpeed;
    QGraphicsTextItem* mStatusDefensive;
    QGraphicsTextItem* mStatusLucky;
    QGraphicsTextItem* mStatusAttack;

    ButtonItem* mEndTurnBtn = nullptr;
    bool mAllowEndTurn = true;

    QSoundEffect* mToggleHUDSound;

    void initHud();
    void initTitleBar();
    void initStatusPanel();
    void initNextTurnBtn();

    QGraphicsDropShadowEffect* createShadow(int offsetX = 5, int offsetY = 5, int blur = 20);
    void deleteItemGroup(QGraphicsItemGroup* group);

};

#endif // HUD_H
