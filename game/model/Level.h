#ifndef LEVEL_H
#define LEVEL_H

#include "item/LevelCellItem.h"
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QJsonArray>
#include <QJsonObject>

class Level
{
public:
    Level();
    virtual ~Level();

    Level(const Level& ano) = delete;


    const QVector<QVector<LevelCellItem*>> &cellRows() const;
    void setScene(QGraphicsScene *newScene);

    inline int levelWidth() {return mCellRows[0].size();}
    inline int levelHeight() {return mCellRows.size();}
    inline bool isEmpty() {return mCellRows[0][0] == nullptr;}
    inline bool canPlaceGameModel(QPoint p){
        if(mCellRows.empty()) return false;
        if(mCellRows[0].empty()) return false;
        if(mCellRows[0][0] == nullptr) return false;
        if(p.x() < 0 || p.x() >= mCellRows[0].size()) return false;
        if(p.y() < 0 || p.y() >= mCellRows.size()) return false;
        switch(mCellRows[p.y()][p.x()]->cellType()){
        case LevelCellItem::CellType::Grass: return true;
        case LevelCellItem::CellType::Stone: return true;
        }
        return false;
    }

    void load(const QJsonArray& arr);

    //edit level
    void initLevel(const int w, const int h);
    void setStonePath(const QRect rect);
    void setWallRect(const QRect rect);

    //test only
    void _gen();

private:
    QVector<QVector<LevelCellItem*>> mCellRows;
    QGraphicsScene *mScene;

    void clear();
    void takeCells();
    void addCells();
};

#endif // LEVEL_H
