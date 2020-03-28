#pragma once

#include "../Utilities/Macro.h"
#include "../Utilities/SubActionManager.h"
#include "../JSON/Specialized/JSONPendu.h"

#include <QString>
#include <QDebug>

class Pendu
{
public:
    Pendu();
    ~Pendu();

    enum class InformationType {
        general
    };

    SubActionManager::Action funcPendu(QList<QString> args, int index);

    SubActionManager::Action Play(QList<QString> args, int index);
    SubActionManager::Action Remove(QList<QString> args, int index);
    SubActionManager::Action Add(QList<QString> args, int index);

    void QStringToUnderScore(QString* Str, QVector<int> Discovered);
    void QStringToUnderScore(QString* Str);

    void GiveInformation(InformationType Type);

private:
    QList<QString> cmdList = { expINPUT, expCANCEL, expSHOW, expREMOVE, expPLAY };
};
