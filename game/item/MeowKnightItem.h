#ifndef MEOWKNIGHT_H
#define MEOWKNIGHT_H

#include "util/AsepriteObject.h"
#include "GameCharItem.h"
#include <QString>
#include <QTimer>
#include <QPropertyAnimation>

class MeowKnightItem : public GameCharItem
{
    Q_OBJECT
    Q_PROPERTY(bool animating READ animating WRITE setAnimating NOTIFY animatingChanged)

signals:
    void animatingChanged(bool a);
    void animationAutoStopped(const QString name);

public:
    constexpr static int ZValue = 200;

    MeowKnightItem(const QString& color, QGraphicsObject* parent = nullptr);
    ~MeowKnightItem();

    // future: use polymorphic to substitude if-else
    struct AnimationName{
        constexpr static const char* Run = "Run";
        constexpr static const char* Idle = "Idle"; // there is no animation for Idle state
        constexpr static const char* Jump = "Jump";
        constexpr static const char* Attack = "Attack_2";
        constexpr static const char* AttackWithSkill = "Attack_1";
        constexpr static const char* Dodge = "Dodge";
        constexpr static const char* TakeDamage = "Take_Damage";
        constexpr static const char* Death = "Death";
    };

    struct Colors {
        constexpr static const char* Grey = "grey";

    };

    static AsepriteObject* loadMeowAseprite(const QString& color);

    void playAnimation(const QString& name);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool autoStop() const;
    void setAutoStop(bool newAutoStop);
    bool playing() const;
    void setPlaying(bool newPlaying);

    // Animation
    inline bool animating() const { return mAnimating;}
    inline void setAnimating(const bool a) {
        if(a == mAnimating) return;
        mAnimating = a;
        emit animatingChanged(mAnimating);
    }

    constexpr static int MOVE_DURATION = 800;
    bool idle() override;
    bool moveTo(const QPointF pos) override;
    bool dodge() override;
    bool attack() override;
    bool takeDamage() override;
    bool death() override;
    void setTowards(bool towardRight = true) override;


    // QGraphicsItem interface
protected:

    // for debug only
    void keyReleaseEvent(QKeyEvent *event) override;

    // update zvalue
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;


private:
    QString mColor = "grey";
    AsepriteObject *mAseObj = nullptr;
    QString mCurAnimation;
    bool mAutoStop = true;
    bool mPlaying = true;
    QRect mBoundingRect;
    QTimer *mTimer;
    bool mTowardRight = true;

    void nextFrame();
    bool needAutoStop();
    const char* nextAnimation();

    // animation
    bool mAnimating = false;
};



#endif // MEOWKNIGHT_H
