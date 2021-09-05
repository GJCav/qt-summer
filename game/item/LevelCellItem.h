#ifndef LEVELCELLITEM_H
#define LEVELCELLITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QJsonObject>

class LevelCellItem : public QGraphicsItem
{
public:
    constexpr static int ZValue = 0;
    struct CellType{
        constexpr static int None = 0;

        constexpr static int Grass = 100;
        constexpr static int Stone = 200;

        constexpr static int WallLeft =  300;
        constexpr static int WallTopLeft =  301;
        constexpr static int WallTopRight =  302;
        //constexpr static int WallTop3 =  303;
        constexpr static int WallRight = 304;
        constexpr static int WallBottomLeft = 305;
        constexpr static int WallBottomRight = 306;
        //constexpr static int WallDown3 = 307;

        constexpr static int WallCnrLT = 400;
        constexpr static int WallCnrRT = 401;
        constexpr static int WallCnrLB = 402;
        constexpr static int WallCnrRB = 403;

        constexpr static int Shadow = 2000;
    };

    constexpr static int CellSize = 64;

public:
    LevelCellItem(const int type = 0, QGraphicsItem* parent = nullptr);

    int cellType() const;
    void setCellType(int type);
    const QPixmap& texture() const;
    void setTexture(const QPixmap& newTexture);

    void loadFromJson(const QJsonObject& obj);
    QJsonObject saveToJson() const;

private:
    QPixmap mTexture;
    int mCellType;



    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // LEVELCELLITEM_H
