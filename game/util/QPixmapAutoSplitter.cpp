#include "QPixmapAutoSplitter.h"

#include <queue>

QPixmapAutoSplitter::QPixmapAutoSplitter()
{

}

QPixmapAutoSplitter::QPixmapAutoSplitter(QString srcPath)
{
    setPixmap(QPixmap(srcPath));
}

void QPixmapAutoSplitter::setSplitThreshold(int newSplitThreshold)
{
    if(mSplitThreshold == newSplitThreshold) return;
    mSplitThreshold = newSplitThreshold;
    recalculate();
}

QRect QPixmapAutoSplitter::floodFillSearch(const QPoint pos, StateMap &state, const QImage& image)
{
    const static int dirX[] = {-1, 0, 1,  0};
    const static int dirY[] = {0,  1, 0, -1};

    QRect rect(pos, pos);

    std::queue<QPoint> que;
    que.push(pos);
    while(!que.empty()){
        QPoint h = que.front();
        que.pop();

        for(int i = 0;i < 4;i++){
            const int x = h.x() + dirX[i];
            const int y = h.y() + dirY[i];

            if(x < 0 || x >= image.width()) continue;
            if(y < 0 || y >= image.height()) continue;

            if(state[y][x] != -1) continue;
            if(isTransparentColor(image.pixelColor(x, y))){
                const int d = state[h.y()][h.x()] + 1;
                if(d > mSplitThreshold) continue;
                state[y][x] = d;
                que.push({x, y});
            }else{
                updateRect(rect, {x, y});
                state[y][x] = 0;
                que.push({x, y});
            }

        }
    }

    return rect;
}


void QPixmapAutoSplitter::calculateRects()
{
    StateMap state;
    for(int i = 0;i < mPixmap.height();i++){
        state.push_back(std::vector<int>(mPixmap.width(), -1));
    }
    QImage image = mPixmap.toImage();

    for(int i = 0;i < mPixmap.height();i++){
        for(int j = 0;j < mPixmap.width();j++){
            if(state[i][j] != -1){
                continue;
            }
            if(isTransparentColor(image.pixelColor(j, i))){
                continue;
            }
            state[i][j] = 0;
            QRect newRect = floodFillSearch({j, i}, state, image);
            mSubPixmapRects.append(newRect);
        }
    }
}



















