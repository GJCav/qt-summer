#ifndef GAMEPROP_H
#define GAMEPROP_H

#include "item/PropItem.h"
#include "item/LevelCellItem.h"
#include "GameScene.h"
#include <QObject>

class GameProp : public QObject
{
    Q_OBJECT
public:
    // 这个和PropItem保持一致
    struct PropType{
        constexpr static int None = 0;
        constexpr static int Chest = 100;
        constexpr static int Magic = 200;
        constexpr static int Stone = 300;
        constexpr static int Vase = 400;
    };

    constexpr static int CellSize = LevelCellItem::CellSize;

public:
    explicit GameProp(GameScene *game, int type = PropType::None);
    QPoint pos() const;
    void setPos(QPoint newPos);
    inline void setPos(int x, int y) { setPos(QPoint{x, y});}
    PropItem *propItem() const;

    int propType() const;

signals:
    void clicked(GameProp *);

private:
    GameScene* mGame;

    int mPropType = PropType::None;
    PropItem* mPropItem = nullptr;

    QPoint mPos; // pos on the GameScene

private slots:
    void clickOn(PropItem* item);

};

#endif // GAMEPROP_H
