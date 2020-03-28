#pragma once

#include <QString>
#include <qrandom.h>
#include <QDebug>

#include "../Utilities//Macro.h"

#include "../Utilities/SubActionManager.h"

class POM
{
public:
    POM();
    ~POM();

    SubActionManager::Action FuncPlusOuMoins(QList<QString> args);

    enum class TypeOfInfo
    {
        General, HigherNum, LowerNum
    };

    bool POM_RandomNumber(int _intLower, int _intHigher, int& _intResult);
    void POM_GiveInformation(TypeOfInfo Type);
    void POM_PrintErrorMessageInt();
    void POM_PrintErrorMessageLowHight();
};
