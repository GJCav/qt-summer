#include "MeowKnightItem.h"
#include "R.h"

MeowKnightItem::MeowKnightItem(const QString &color, QGraphicsItem* parent)
    : QGraphicsItem(parent), mColor(color)
{
    mAseObj = loadMeowAseprite(color);
    mTimer = new QTimer();
    mTimer->setSingleShot(true);
    mTimer->callOnTimeout([this](){nextFrame();});

    playAnimation(AnimationName::Idle);

    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    //this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    //this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

MeowKnightItem::~MeowKnightItem()
{
    delete mAseObj;
    delete mTimer;
}

AsepriteObject *MeowKnightItem::loadMeowAseprite(const QString &name)
{
    const QString rootPath = ":/asset/Meow Knight/";
    const QString jsonPath = ":/asset/Meow Knight/Meow_Knight.json";

    const QString pngPath = rootPath+name+QString(".png");
    AsepriteObject* const obj = new AsepriteObject();
    obj->setJsonPath(jsonPath);
    obj->setTexturePixmap(pngPath);

    return obj;
}

bool MeowKnightItem::autoStop() const
{
    return mAutoStop;
}

void MeowKnightItem::setAutoStop(bool newAutoStop)
{
    if(mAutoStop == newAutoStop) return;
    mAutoStop = newAutoStop;
}

bool MeowKnightItem::playing() const
{
    return mPlaying;
}

void MeowKnightItem::setPlaying(bool newPlaying)
{
    if(mPlaying == newPlaying) return;
    mPlaying = newPlaying;
    if(mPlaying == true){
        mTimer->start(mAseObj->duration());
    }else{
        mTimer->stop();
    }
}

void MeowKnightItem::nextFrame()
{
    if(!mPlaying) return;
    mAseObj->nextFrame();
    update();

    if(needAutoStop()){
        auto next = nextAnimation();
        if(next != nullptr){
            playAnimation(next);
        }
    }else{
        mTimer->start(mAseObj->duration());
    }
}

bool MeowKnightItem::needAutoStop()
{
    if(!mAutoStop) return false;
    if(!mAseObj->isEndFrame()) return false;
    if(mCurAnimation == AnimationName::Jump) return true;
    if(mCurAnimation == AnimationName::Attack) return true;
    if(mCurAnimation == AnimationName::AttackWithSkill) return true;
    if(mCurAnimation == AnimationName::Dodge) return true;
    if(mCurAnimation == AnimationName::TakeDamage) return true;
    if(mCurAnimation == AnimationName::Death) return true;
    return false;
}

const char *MeowKnightItem::nextAnimation()
{
    if(mCurAnimation == AnimationName::Death) return nullptr;
    return AnimationName::Idle;
}

QRectF MeowKnightItem::boundingRect() const
{
    return mBoundingRect;
}

void MeowKnightItem::playAnimation(const QString &name)
{
    if(mCurAnimation == name) return;
    if(mTimer->isActive()){
        mTimer->stop();
    }
    mCurAnimation = name;

    mAseObj->useTag(mCurAnimation);
    prepareGeometryChange();
    if(mCurAnimation == AnimationName::Idle){
        mBoundingRect = {0, 0, 16, 16};
    }else if(mCurAnimation == AnimationName::Run){
        mBoundingRect = {0, -1, 16, 17};
    }else if(mCurAnimation == AnimationName::Jump){
        mBoundingRect = {0, 0, 16, 20};
    }else if(mCurAnimation == AnimationName::Attack){
        mBoundingRect = {-5, -8, 41, 24};
    }else if(mCurAnimation == AnimationName::AttackWithSkill){
        mBoundingRect = {-16, -16, 48, 32};
    }else if(mCurAnimation == AnimationName::Dodge){
        mBoundingRect = {-16, 0, 32, 16};
    }else if(mCurAnimation == AnimationName::TakeDamage){
        mBoundingRect = {0, 0, 16, 16};
    }else if(mCurAnimation == AnimationName::Death){
        mBoundingRect = {0, 0, 32, 16};
    }else{
        Q_ASSERT_X(false, "MeowKnightItem::playAnimation", "Unsupport animation.");
    }
    update();
    mTimer->start(mAseObj->duration());
}

void MeowKnightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::red);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawRect(mBoundingRect);
    if(mCurAnimation == AnimationName::Idle){
        painter->drawPixmap(0, 0, mAseObj->pixmap());
    }else if(mCurAnimation == AnimationName::Run){
        auto pixmap = mAseObj->pixmap();
        if(pixmap.height() == 16){
            painter->drawPixmap(0, 0, pixmap);
        }else{
            painter->drawPixmap(QRect{0, -1, 16, 17}, pixmap, {0, 15, 16, 17});
        }
    }else if(mCurAnimation == AnimationName::Jump){
        painter->drawPixmap(0, 0, mAseObj->pixmap());
    }else if(mCurAnimation == AnimationName::Attack){
        switch(mAseObj->currentFrameIndex()){
        case 0: painter->drawPixmap(
                        QRect{-5, -8, 21, 24},
                        mAseObj->pixmap(),
                        QRect{11, 9, 21, 24}
                        );
                break;
        case 1: painter->drawPixmap(
                        QRect{0, -4, 29, 20},
                        mAseObj->pixmap(),
                        QRect{0, 12, 29, 20}
                        );
                break;
        case 2: painter->drawPixmap(
                        QRect{0, -3, 33, 19},
                        mAseObj->pixmap(),
                        QRect{0, 13, 33, 19}
                        );
                break;
        case 3: painter->drawPixmap(
                        QRect{0, 0, 36, 16},
                        mAseObj->pixmap(),
                        QRect{0, 0, 36, 16}
                        );
                break;
        }
    }else if(mCurAnimation == AnimationName::AttackWithSkill){
        switch(mAseObj->currentFrameIndex()){
        case 0: painter->drawPixmap(-16, -16, mAseObj->pixmap()); break;
        case 1: painter->drawPixmap(-16, -16, mAseObj->pixmap()); break;
        case 2: painter->drawPixmap(-16, -16, mAseObj->pixmap()); break;
        case 3: painter->drawPixmap(0, -16, mAseObj->pixmap()); break;
        case 4:
        case 5:
        case 6: painter->drawPixmap(0, 0, mAseObj->pixmap()); break;
        case 7:
        case 8:
        case 9: painter->drawPixmap(0, 0, mAseObj->pixmap());
                break;
        }
    }else if(mCurAnimation == AnimationName::Dodge){
        if(mAseObj->currentFrameIndex() == 3){
            painter->drawPixmap(-16, 0, mAseObj->pixmap());
        }else{
            painter->drawPixmap(0, 0, mAseObj->pixmap());
        }
    }else if(mCurAnimation == AnimationName::TakeDamage){
        painter->drawPixmap(0, 0, mAseObj->pixmap());
    }else if(mCurAnimation == AnimationName::Death){
        painter->drawPixmap(0, 0, mAseObj->pixmap());
    }
}

void MeowKnightItem::keyReleaseEvent(QKeyEvent *event)
{
    //return;
    switch(event->key()){
    case Qt::Key_R: playAnimation(AnimationName::Run); break;
    case Qt::Key_I: playAnimation(AnimationName::Idle); break;
    case Qt::Key_J: playAnimation(AnimationName::Jump); break;
    case Qt::Key_A: playAnimation(AnimationName::Attack); break;
    case Qt::Key_S: playAnimation(AnimationName::AttackWithSkill); break;
    case Qt::Key_D: playAnimation(AnimationName::Dodge); break;
    case Qt::Key_T: playAnimation(AnimationName::TakeDamage); break;
    case Qt::Key_K: playAnimation(AnimationName::Death); break;
    }
}

QVariant MeowKnightItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene()){
        QPoint newPos = value.toPoint();
        setZValue(ZValue+newPos.y()+mBoundingRect.height() * scale());
    }
    return QGraphicsItem::itemChange(change, value);
}


















