#pragma once

#include <QDebug>
#include <QString>
#include <QtCore/QCoreApplication>

#include "../Modes/Caesar.h"
#include "../Modes/POM.h"
#include "../Modes/Pendu.h"

#include "../Utilities/Macro.h"

class ComManager
{
public:
    ComManager();
    ~ComManager();

    enum class Events
    {
        Quit, Back, Info, Clear, Caesar, PlusOuMoins, Pendu
    };

    void Menu();

    void Info();

    SubActionManager::Action FromStringToType(QList<QString> args);
    SubActionManager::Action CheckFor(QList<QString> args, ComManager::Events _Type);
};
