#ifndef ASEPRITEITEM_H
#define ASEPRITEITEM_H

#include <QGraphicsPixmapItem>
#include <QVector>

class AsepriteObject
{
public:
    AsepriteObject();

    const QString &jsonPath() const;
    void setJsonPath(const QString &newJsonPath);
    const QPixmap &texturePixmap() const;
    void setTexturePixmap(const QPixmap &newTexturePixmap);

    void reclip();
    void useTag(const QString& tag);
    void nextFrame();

    // current frame infomation
    const QPixmap& pixmap() const;
    const int duration() const;
    const QString tag() const { return mCurTag;}


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
