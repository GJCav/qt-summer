#ifndef GAMECHARITEM_H
#define GAMECHARITEM_H

#include <QGraphicsObject>

class GameCharItem : public QGraphicsObject
{
    Q_OBJECT
public:
    constexpr static int ZValue = 200;
    GameCharItem(QGraphicsObject* parent = nullptr);
    virtual ~GameCharItem(){}

    // function to play animation and set properties.
    virtual bool idle() = 0;
    virtual bool moveTo(const QPointF pos) = 0;
    virtual bool attack() = 0;
    virtual bool takeDamage(const qreal hurt) = 0;
    virtual bool healed(const qreal heal) = 0;
    virtual bool death() = 0;
    virtual bool dodge() = 0;
    virtual void setTowards(bool towardRight = true) = 0;

signals:
    void selectedChange(bool selected);
    void clicked(GameCharItem* self);

    // QGraphicsItem interface
protected:
    // remember to call this if subclass overrides this.
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private slots:
    void updateZValue();

};

#endif // GAMECHARITEM_H
