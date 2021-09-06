#include "MeowKnightItem.h"
#include "R.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

MeowKnightItem::MeowKnightItem(const QString &color, QGraphicsObject* parent)
    : GameCharItem(parent), mColor(color)
{
    mAseObj = loadMeowAseprite(color);
    mTimer = new QTimer();
    mTimer->setSingleShot(true);
    mTimer->callOnTimeout([this](){nextFrame();});

    // auto update z-index
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    // animation
    playAnimation(AnimationName::Idle);

    // selection indicator
    mSltIdrItem = new SelectIndicatorItem(this);
    mSltIdrItem->setParentItem(this);
    mSltIdrItem->setPos({8, 0});
    mSltIdrItem->setVisible(false);

    // debug only
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
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

bool MeowKnightItem::idle()
{
    if(animating()) return false;
    playAnimation(AnimationName::Idle);
    return true;
}

bool MeowKnightItem::moveTo(const QPointF target)
{
    if(mAnimating) return false;
    QPointF curPos = pos();
    mTowardRight = target.x() > curPos.x();

    QPropertyAnimation *mMoveXAnimation = new QPropertyAnimation(this);
    mMoveXAnimation->setTargetObject(this);
    mMoveXAnimation->setPropertyName("x");

    QPropertyAnimation *mMoveYAnimation = new QPropertyAnimation(this);
    mMoveYAnimation->setTargetObject(this);
    mMoveYAnimation->setPropertyName("y");

    mMoveXAnimation->setStartValue(curPos.x());
    mMoveXAnimation->setEndValue(target.x());
    mMoveXAnimation->setDuration(MOVE_DURATION);
    mMoveXAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    mMoveYAnimation->setStartValue(curPos.y());
    mMoveYAnimation->setEndValue(target.y());
    mMoveYAnimation->setDuration(MOVE_DURATION);
    mMoveYAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(mMoveXAnimation);
    group->addAnimation(mMoveYAnimation);
    connect(group, &QAnimationGroup::finished, [this, group](){
        this->setAnimating(false);
        group->deleteLater();
        this->playAnimation(AnimationName::Idle);
    });
    setAnimating(true);
    playAnimation(AnimationName::Run);
    group->start();

    return true;
}

bool MeowKnightItem::dodge()
{
    if(animating()) return false;

    QGraphicsTextItem *miss = new QGraphicsTextItem("miss", this);
    miss->setDefaultTextColor(Qt::yellow);
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSizeF(4);
    miss->setFont(font);
    miss->setPos(-2, -8);

    constexpr static QPointF beginPos = {-2, -8};
    constexpr static QPointF endPos = {-2, -13};
    constexpr static int duration = 300;

    auto opacityAni = new QPropertyAnimation(this);
    opacityAni->setTargetObject(miss);
    opacityAni->setPropertyName("opacity");
    opacityAni->setStartValue(1);
    opacityAni->setEndValue(0);
    opacityAni->setKeyValueAt(0.3, 1);
    opacityAni->setDuration(duration);
    opacityAni->setEasingCurve(QEasingCurve::InCubic);

    auto moveAni = new QPropertyAnimation(this);
    moveAni->setTargetObject(miss);
    moveAni->setPropertyName("pos");
    moveAni->setStartValue(beginPos);
    moveAni->setEndValue(endPos);
    moveAni->setKeyValueAt(0.3, beginPos);
    moveAni->setDuration(duration);

    auto group = new QParallelAnimationGroup(this);
    group->addAnimation(moveAni);
    group->addAnimation(opacityAni);
    connect(group, &QParallelAnimationGroup::finished, [this, group](){
        group->deleteLater();
        setAnimating(false);
    });
    setAnimating(true);
    group->start();
    playAnimation(AnimationName::Dodge);

    return true;
}

bool MeowKnightItem::attack()
{
    if(animating()) return false;
    setAnimating(true);
    connect(this, &MeowKnightItem::animationAutoStopped, this, [this](){
        setAnimating(false);
    }, Qt::SingleShotConnection);
    playAnimation(AnimationName::Attack);
    return true;
}

bool MeowKnightItem::takeDamage()
{
    if(animating()) return false;
    setAnimating(true);
    connect(this, &MeowKnightItem::animationAutoStopped, this, [this](){
        setAnimating(false);
    }, Qt::SingleShotConnection);
    playAnimation(AnimationName::TakeDamage);
    return true;
}

bool MeowKnightItem::death()
{
    if(animating()) return false;
    setAnimating(true);
    playAnimation(AnimationName::Death);
    QTimer::singleShot(mAseObj->getAnimationTime(AnimationName::Death), this, [this](){
        setAnimating(false);
    });
    return true;
}

void MeowKnightItem::setTowards(bool towardRight)
{
    mTowardRight = towardRight;
}

void MeowKnightItem::nextFrame()
{
    if(!mPlaying) return;
    mAseObj->nextFrame();
    update();

    if(needAutoStop()){
        emit animationAutoStopped(mCurAnimation);
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
//    prepareGeometryChange();
//    if(mCurAnimation == AnimationName::Idle){
//        mBoundingRect = {0, 0, 16, 16};
//    }else if(mCurAnimation == AnimationName::Run){
//        mBoundingRect = {0, -1, 16, 17};
//    }else if(mCurAnimation == AnimationName::Jump){
//        mBoundingRect = {0, 0, 16, 20};
//    }else if(mCurAnimation == AnimationName::Attack){
//        mBoundingRect = {-5, -8, 41, 24};
//    }else if(mCurAnimation == AnimationName::AttackWithSkill){
//        mBoundingRect = {-16, -16, 48, 32};
//    }else if(mCurAnimation == AnimationName::Dodge){
//        mBoundingRect = {-16, 0, 32, 16};
//    }else if(mCurAnimation == AnimationName::TakeDamage){
//        mBoundingRect = {0, 0, 16, 16};
//    }else if(mCurAnimation == AnimationName::Death){
//        mBoundingRect = {0, 0, 32, 16};
//    }else{
//        Q_ASSERT_X(false, "MeowKnightItem::playAnimation", "Unsupport animation.");
//    }
    mBoundingRect = {-16, -16, 3*16, 2*16};
    update();
    mTimer->start(mAseObj->duration());
}

void MeowKnightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(mTowardRight){

    }else{
        painter->translate(16, 0);
        painter->scale(-1, 1);
    }

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

//    QPen pen(Qt::red);
//    pen.setCosmetic(true);
//    painter->setPen(pen);
//    painter->drawRect(mBoundingRect);
//    painter->drawEllipse(-3, -3, 6, 6);
}

void MeowKnightItem::keyReleaseEvent(QKeyEvent *event)
{
    //return;

    switch(event->key()){
    case Qt::Key_R: playAnimation(AnimationName::Run); break;
    case Qt::Key_I: idle(); break;
    case Qt::Key_J: playAnimation(AnimationName::Jump); break;
    case Qt::Key_A: attack(); break;
    case Qt::Key_S: playAnimation(AnimationName::AttackWithSkill); break;
    case Qt::Key_D: dodge(); break;
    case Qt::Key_T: takeDamage(); break;
    case Qt::Key_K: death(); break;
    case Qt::Key_F:
//        QTransform t = transform();
//        t.scale(-1, 1);
//        setTransformOriginPoint(8, 0);
//        setTransform(t);
//        setTransformOriginPoint(0, 0);
        mTowardRight = !mTowardRight;
        update();
        break;
    case Qt::Key_Right:{
        QPointF p = pos();
        moveTo({p.x() + 60, p.y() + 30});
        break;
    }

    case Qt::Key_Left:{
        QPointF p = pos();
        moveTo({p.x() - 60, p.y() - 30});
        break;
    }
    }
}

QVariant MeowKnightItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene()){
        QPoint newPos = value.toPoint();
        setZValue(ZValue+newPos.y()+mBoundingRect.height() * scale());
    }

    if(change == ItemSelectedHasChanged && scene()){
        if(value.toBool() && mEnableSelectIndicator){
            mSltIdrItem->setVisible(true);
        }else{
            mSltIdrItem->setVisible(false);
        }
    }
    return GameCharItem::itemChange(change, value);
}

QPainterPath MeowKnightItem::shape() const
{
    QPainterPath path;
    path.addRect({0, 0, 16, 16});
    return path;
}
