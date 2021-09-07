#ifndef HUD_H
#define HUD_H

#include "item/hud/IconItem.h"
#include "item/hud/ButtonItem.h"
#include "ui/LightWoodPanel.h"
#include "GameScene.h"
#include "model/GameCharAction.h"
#include <QObject>
#include <QVector>
#include <QLabel>
#include <QGraphicsItemGroup>
#include <QGraphicsDropShadowEffect>

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

    inline void setStatusName(const QString& s) {mStatusName->setPlainText(s);}
    inline void setStatusHealth(const QString& s) {mStatusHealth->setPlainText(s);}
    inline void setStatusSpeed(const QString& s) {mStatusSpeed->setPlainText(s);}
    inline void setStatusDefensive(const QString& s){mStatusDefensive->setPlainText(s);}
    inline void setStatusLucky(const QString& s) {mStatusLucky->setPlainText(s);}
    inline void setStatusAttack(const QString& s) {mStatusAttack->setPlainText(s);}
    inline void setStatusName(int n) {setStatusName(QString::number(n));}
    inline void setStatusHealth(int n) {setStatusHealth(QString::number(n));}
    inline void setStatusSpeed(int n) {setStatusSpeed(QString::number(n));}
    inline void setStatusDefensive(int n) {setStatusDefensive(QString::number(n));}
    inline void setStatusLucky(int n) { setStatusLucky(QString::number(n));}
    inline void setStatusAttack(int n) { setStatusAttack(QString::number(n));}

    void toggleHUD();
    inline bool visible() const { return mVisible;}
    inline bool actActBtnVisible() const {return mActBtnVisible;}
    inline void toggleActBtn() {
        mActBtnVisible = !mActBtnVisible;
        mActBtnGroup->setVisible(mActBtnVisible & mVisible);
    };

private:
    bool mVisible = true;
    bool mActBtnVisible = true;

    GameScene *mGame;

    QGraphicsProxyWidget* mTitleProxy;
    LightWoodPanel* mTitlePanel;
    QLabel *mTitleLabel;

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

    void initHud();
    void initTitleBar();
    void initStatusPanel();

    QGraphicsDropShadowEffect* createShadow(int offsetX = 5, int offsetY = 5, int blur = 20);
    void deleteItemGroup(QGraphicsItemGroup* group);

};

#endif // HUD_H
