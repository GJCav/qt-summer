#ifndef MEOWKNIGHT_H
#define MEOWKNIGHT_H

#include "util/AsepriteObject.h"
#include <QString>
#include <QTimer>

class MeowKnightItem : public QGraphicsItem
{
public:
    MeowKnightItem(const QString& color, QGraphicsItem* parent = nullptr);
    ~MeowKnightItem();

    // future: use polymorphic to substitude if-else
    struct AnimationName{
        constexpr static const char* Run = "Run";
        constexpr static const char* Idle = "Idle";
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



private:
    QString mColor = "grey";
    AsepriteObject *mAseObj = nullptr;
    QString mCurAnimation;
    bool mAutoStop = true;
    bool mPlaying = true;
    QRect mBoundingRect;
    QTimer *mTimer;

    void nextFrame();
    bool needAutoStop();
    const char* nextAnimation();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool autoStop() const;
    void setAutoStop(bool newAutoStop);
    bool playing() const;
    void setPlaying(bool newPlaying);

    // QGraphicsItem interface
protected:

    // for debug only
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MEOWKNIGHT_H
