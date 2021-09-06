#include "LevelCellItem.h"
#include "R.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

LevelCellItem::LevelCellItem(const int type, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setCellType(type);
}

int LevelCellItem::cellType() const
{
    return mCellType;
}

void LevelCellItem::setCellType(int type)
{
    mCellType = type;
    switch(type){
    case CellType::Grass:
        setTexture(R::Level::GrassTextureProvider->subPixmapAt(QRandomGenerator::global()->generate()%64));
        break;
    case CellType::Stone:
        setTexture(R::Level::GrassWithStoneTextureProvider->subPixmapAt(QRandomGenerator::global()->generate()%64));
        break;
    case CellType::WallTopLeft:
        setTexture(R::Level::WallPixmap->copy(400, 64, 16, 16));
        break;
    case CellType::WallTopRight:
        setTexture(R::Level::WallPixmap->copy(416, 64, 16, 16));
        break;
    case CellType::WallRight:
        setTexture(R::Level::WallPixmap->copy(432, 80, 16, 16));
        break;
    case CellType::WallLeft:
        setTexture(R::Level::WallPixmap->copy(384, 80, 16, 16));
        break;
    case CellType::WallBottomLeft:
        setTexture(R::Level::WallPixmap->copy(400, 96, 16, 16));
        break;
    case CellType::WallBottomRight:
        setTexture(R::Level::WallPixmap->copy(416, 96, 16, 16));
        break;
    case CellType::WallCnrLT:
        setTexture(R::Level::WallPixmap->copy(384, 64, 16, 16));
        break;
    case CellType::WallCnrRT:
        setTexture(R::Level::WallPixmap->copy(432, 64, 16, 16));
        break;
    case CellType::WallCnrLB:
        setTexture(R::Level::WallPixmap->copy(384, 96, 16, 16));
        break;
    case CellType::WallCnrRB:
        setTexture(R::Level::WallPixmap->copy(432, 96, 16, 16));
        break;
    }
}

const QPixmap& LevelCellItem::texture() const
{
    return mTexture;
}

void LevelCellItem::setTexture(const QPixmap& newTexture)
{
    if(&mTexture == &newTexture) return;
    mTexture = newTexture;
    update();
}

void LevelCellItem::loadFromJson(const QJsonObject &obj)
{
    //setHeight(obj.value("height").toInt());
    setCellType(obj.value("type").toInt());
}

QJsonObject LevelCellItem::saveToJson() const
{
    QJsonObject obj;
    //obj.insert("height", height());
    obj.insert("type", mCellType);
    return obj;
}


QRectF LevelCellItem::boundingRect() const
{
    return {0, 0, CellSize, CellSize};
}


void LevelCellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    auto txt = texture();
    painter->drawPixmap(
        boundingRect(),
        txt,
        txt.rect()
    );
}
