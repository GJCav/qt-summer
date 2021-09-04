#ifndef ASEPRITEITEM_H
#define ASEPRITEITEM_H

#include <QGraphicsPixmapItem>
#include <QVector>

class AsepriteObject
{
public:
    AsepriteObject();

    struct Tag{
        QString name;
        int from = 0;
        int to = 0;
        QString direction;
    };

    struct Frame {
        QRect rect;
        int duration = 0;
    };

    const QString &jsonPath() const;
    void setJsonPath(const QString &newJsonPath);
    const QPixmap &texturePixmap() const;
    void setTexturePixmap(const QPixmap &newTexturePixmap);

    void reclip();
    void useTag(const QString& tag);
    void nextFrame();

    // current frame infomation
    const QPixmap& pixmap() const;
    int duration() const;
    const QString tag() const { return mCurTag;}
    int currentFrameIndex() const {return mCurFrameIndex - mTags[mCurTag].from;}
    bool isBeginFrame() const { return mCurFrameIndex == mTags[mCurTag].from;}
    bool isEndFrame() const {return mCurFrameIndex == mTags[mCurTag].to;}

    // infomation of an action tag
    const Tag getTag(const QString& name) const { return mTags.value(name); }
    int getAnimationTime(const QString& name) const {
        const int from = mTags.value(name).from;
        const int to = mTags.value(name).to;
        int totTime = 0;
        for(int i = from;i <= to;i++){
            totTime += mFrames[i].duration;
        }
        return totTime;
    }
    const QString getAnimationDirection(const QString& name) const {
        return getTag(name).direction;
    }

private:
    QString mJsonPath;
    QPixmap mTexturePixmap;
    QVector<Frame> mFrames;
    QVector<QPixmap> mFramePixmaps;
    QMap<QString, Tag> mTags;

    int mCurFrameIndex;
    QString mCurTag;


};

#endif // ASEPRITEITEM_H
