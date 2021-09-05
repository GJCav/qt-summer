#include "Level.h"
#include "item/LevelCellItem.h"

using CellType = LevelCellItem::CellType;

Level::Level()
{
    mCellRows.append({nullptr});
}

Level::~Level()
{
    clear();
}

const QVector<QVector<LevelCellItem*>> &Level::cellRows() const
{
    return mCellRows;
}

void Level::setScene(QGraphicsScene *newScene)
{
    if(mScene == newScene) return;
    if(mScene != nullptr) takeCells();
    mScene  = newScene;
    addCells();
}

void Level::load(const QJsonArray &arr)
{
    clear();
    mCellRows.clear();

    for(int i = 0;i < arr.size();i++){
        QVector<LevelCellItem*> row;
        auto rowJson = arr.at(i).toArray();
        for(int j = 0;j < rowJson.size();j++){
            LevelCellItem *item = new LevelCellItem();
            item->loadFromJson(rowJson.at(j).toObject());
            row.append(item);
        }
        mCellRows.append(row);
    }

    addCells();
}

void Level::initLevel(const int w, const int h)
{
    if(!isEmpty()) return;
    mCellRows.clear();
    for(int i = 0;i < h;i++){
        mCellRows.append(QVector<LevelCellItem*>{});
        for(int j = 0;j < w;j++){
            mCellRows[i].append(new LevelCellItem(LevelCellItem::CellType::Grass));
        }
    }
}

void Level::setStonePath(const QRect rect)
{
    for(int row = rect.top();row <= rect.bottom();row++){
        for(int col = rect.left();col <= rect.right();col++){
            mCellRows[row][col]->setCellType(LevelCellItem::CellType::Stone);
        }
    }
}

void Level::setWallRect(const QRect rect)
{
    mCellRows[rect.top()][rect.left()]->setCellType(CellType::WallCnrLT);
    mCellRows[rect.top()][rect.right()]->setCellType(CellType::WallCnrRT);
    mCellRows[rect.bottom()][rect.left()]->setCellType(CellType::WallCnrLB);
    mCellRows[rect.bottom()][rect.right()]->setCellType(CellType::WallCnrRB);

    for(int i = rect.left()+1;i <= rect.right()-1;i++){
        mCellRows[rect.top()][i]->setCellType((i-rect.left())%2 ? CellType::WallTopLeft:CellType::WallTopRight);
        mCellRows[rect.bottom()][i]->setCellType((i-rect.left())%2 ? CellType::WallBottomLeft:CellType::WallBottomRight);
    }

    for(int i = rect.top()+1;i <= rect.bottom()-1;i++){
        mCellRows[i][rect.left()]->setCellType(CellType::WallLeft);
        mCellRows[i][rect.right()]->setCellType(CellType::WallRight);
    }
}

void Level::_gen()
{
    if(!isEmpty()) return;
    mCellRows.clear();
    for(int i = 0;i < 5;i++){
        mCellRows.append(QVector<LevelCellItem*>{});
        for(int j = 0;j < 15;j++){
            mCellRows[i].append(new LevelCellItem(LevelCellItem::CellType::Grass));
        }
    }
    for(int i = 5;i < 10;i++){
        mCellRows.append(QVector<LevelCellItem*>{});
        for(int j = 0;j < 15;j++){
            mCellRows[i].append(new LevelCellItem(LevelCellItem::CellType::Stone));
        }
    }
}

void Level::clear()
{
    takeCells();
    for(int i = 0;i < mCellRows.size();i++){
        for(int j = 0;j < mCellRows[i].size();j++){
            delete mCellRows[i][j];
            mCellRows[i][j] = nullptr;
        }
    }
    mCellRows = {{nullptr}};
}

void Level::takeCells()
{
//    if(isEmpty()) return;
//    foreach(auto cellRow, mCellRows){
//        for(int i = 0;i < cellRow.size();i++){
//            mScene->removeItem(cellRow.at(i));
//        }
//    }
}

void Level::addCells()
{
    if(isEmpty()) return;
    for(int i = 0;i < mCellRows.size();i++){
        for(int j = 0;j < mCellRows[i].size();j++){
            LevelCellItem *cell = mCellRows[i][j];
            mScene->addItem(cell);
            cell->setPos(j * LevelCellItem::CellSize, i * LevelCellItem::CellSize);
        }
    }
}
