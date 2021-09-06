#ifndef HUD_H
#define HUD_H

#include "item/hud/IconItem.h"
#include "item/hud/ButtonItem.h"
#include "ui/LightWoodPanel.h"
#include <QObject>
#include <QVector>
#include <QLabel>
#include <QGraphicsItemGroup>

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

    HUD(QGraphicsScene *scene, QObject *parent = nullptr);
    ~HUD();

    void setIcons(const QVector<QPixmap>& iconPixmaps);
    void setActBtns(const QVector<QAction*>& actions);

private:
    QGraphicsScene *mScene;

    QGraphicsProxyWidget* mTitleProxy;
    LightWoodPanel* mTitlePanel;
    QLabel *titleLabel;

    QGraphicsItemGroup *mIconGroup = nullptr;
    QVector<QPixmap> mIconPixmaps;
    QVector<IconItem*> mIcons;

    QGraphicsItemGroup *mActBtnGroup = nullptr;
    //QVector<ButtonItem*> actionBtns;

    void initHud();
    void initTitleBar();

};

#endif // HUD_H
