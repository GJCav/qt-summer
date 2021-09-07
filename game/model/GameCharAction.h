#ifndef GAMECHARACTION_H
#define GAMECHARACTION_H

#include "item/hud/ButtonItem.h"
#include <QAction>
#include <QObject>
#include <QWidget>

class GameCharacter;

class GameCharAction : public QAction
{
    Q_OBJECT

public:
    //explicit GameCharAction(const QString& text, QObject *parent = nullptr);
    explicit GameCharAction(GameCharacter* actor, QObject *parent = nullptr);

    ButtonItem *buttonItem() const;
    void setButtonItem(ButtonItem *newButtonItem);

protected:
    GameCharacter *mActor;
    ButtonItem *mButtonItem = nullptr;

    virtual void process();


private slots:
    inline void callProcess() {process();}
};

#endif // GAMECHARACTION_H
