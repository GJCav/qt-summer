#ifndef GAMECHARACTION_H
#define GAMECHARACTION_H

#include <QAction>
#include <QObject>
#include <QWidget>

class GameCharAction : public QAction
{
    Q_OBJECT
public:
    explicit GameCharAction(const QString& text, QObject *parent = nullptr);
};

#endif // GAMECHARACTION_H
