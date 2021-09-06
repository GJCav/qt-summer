#ifndef GAMECHARITEM_H
#define GAMECHARITEM_H

#include <QGraphicsObject>

class GameCharItem : public QGraphicsObject
{
    Q_OBJECT
public:
    GameCharItem(QGraphicsObject* parent = nullptr);
    virtual ~GameCharItem(){}

    // function to play animation and set properties.
    virtual bool idle() = 0;
    virtual bool moveTo(const QPointF pos) = 0;
    virtual bool attack() = 0;
    virtual bool takeDamage() = 0;
    virtual bool death() = 0;
    virtual bool dodge() = 0;
    virtual void setTowards(bool towardRight = true) = 0;

signals:
    void selectedChange(bool selected);

    // QGraphicsItem interface
protected:
    // remember to call this if subclass overrides this.
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // GAMECHARITEM_H
