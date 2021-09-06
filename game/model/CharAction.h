#ifndef CHARACTION_H
#define CHARACTION_H

#include "GameCharacter.h"
#include <QVector>

class CharAction
{
public:
    CharAction();

protected:
    void action();

private:
    int mTargetCount;
    //GameCharacter* source;
};

#endif // CHARACTION_H
