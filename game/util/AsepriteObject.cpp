#include "AsepriteObject.h"
#include <QtCore>
#include <QtWidgets>

AsepriteObject::AsepriteObject()
{

}

const QString &AsepriteObject::jsonPath() const
{
    return mJsonPath;
}

void AsepriteObject::setJsonPath(const QString &newJsonPath)
{
    if(mJsonPath == newJsonPath) return;
    mJsonPath = newJsonPath;
    reclip();
}

void AsepriteObject::reclip()
{
    if(mTexturePixmap.isNull()) return;
    if(mJsonPath.isNull()) return;

    QFile jsonFile(mJsonPath);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &err);
    if(err.error != QJsonParseError::NoError){
        qDebug("%s", qPrintable(err.errorString()));
        return;
    }

    QJsonObject root = doc.object();

    QJsonArray frames = root["frames"].toArray();
    mFrames.clear();
    mFramePixmaps.clear();
    for(int i = 0;i < frames.size();i++){
        QJsonObject frame = frames.at(i).toObject();
        QJsonObject frameRect = frame["frame"].toObject();
        const int width = frameRect["w"].toInt();
        const int height = frameRect["h"].toInt();
        const int x = frameRect["x"].toInt();
        const int y = frameRect["y"].toInt();
        const int duration = frame["duration"].toInt();

        const Frame frameInfo{{x, y, width, height}, duration};
        mFrames.append(frameInfo);

        mFramePixmaps.append(mTexturePixmap.copy(frameInfo.rect));
    }

    QJsonArray tagsJson = root["meta"].toObject()["frameTags"].toArray();
    mTags.clear();
    for(int i = 0;i < tagsJson.size();i++){
        auto tagJson = tagsJson.at(i).toObject();
        Tag tag {
            tagJson["name"].toString(),
            tagJson["from"].toInt(),
            tagJson["to"].toInt(),
            tagJson["direction"].toString()
        };
        mTags[tag.name] = tag;
    }

    useTag(*mTags.keyBegin());
}

void AsepriteObject::useTag(const QString& tag)
{
    if(mCurTag == tag) return;
    if(!mTags.contains(tag)) return;
    mCurTag = tag;
    auto frameInfo = mTags[mCurTag];
    if(frameInfo.direction == "forward"){
        mCurFrameIndex = frameInfo.from;
    }else{
        qDebug("Unknown direction: %s", qPrintable(frameInfo.direction));
        Q_ASSERT_X(false, "AsepriteObject::useTag", "unsupport direction.");
    }
}

void AsepriteObject::nextFrame()
{
    const auto& frameInfo = mTags[mCurTag];
    if(frameInfo.direction == "forward"){
        mCurFrameIndex++;
        if(mCurFrameIndex == frameInfo.to+1){
            mCurFrameIndex = frameInfo.from;
        }
    }else{
        qDebug("Unknown direction: %s", qPrintable(frameInfo.direction));
        Q_ASSERT_X(false, "AsepriteObject::useTag", "unsupport direction.");
    }
}

const QPixmap &AsepriteObject::pixmap() const
{
    return mFramePixmaps[mCurFrameIndex];
}

const int AsepriteObject::duration() const
{
    return mFrames[mCurFrameIndex].duration;
}

const QPixmap &AsepriteObject::texturePixmap() const
{
    return mTexturePixmap;
}

void AsepriteObject::setTexturePixmap(const QPixmap &newTexturePixmap)
{
    if(&mTexturePixmap == &newTexturePixmap) return;
    mTexturePixmap = newTexturePixmap;
    reclip();
}




