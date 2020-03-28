#pragma once

#include <QString>
#include <QChar>
#include <QDebug>

#include "../Utilities/SubActionManager.h"
#include "../Utilities/Macro.h"
#include "../JSON/Specialized/JSONCaesar.h"

class Caesar
{
public:
    enum class TypeOfInfo {
        Global, Settings, AskKeepSpaces, AskKeepSpecialChar
    };

    enum class TypeOfWarn {
        OneOrTwo, YesOrNo, NumbersOnly
    };

    enum class TypeOfOptions
    {
        KeepSpaces, KeepSpecialChar

    };

    Caesar();
    ~Caesar();


    // --------------  Main  --------------

    SubActionManager::Action FuncCaesar(QList<QString> args);

    SubActionManager::Action Play(QList<QString> args);
    SubActionManager::Action Options();



    // --------------  Options  --------------

    SubActionManager::Action ManageOptions(QString Str, TypeOfOptions Type);




    //Sub func
    QString Translation(QString _Str, int _Number);
    int LoopInAString(QString _Str, int _num);

    void GiveInfo(TypeOfInfo Type);
    void GiveWarn(TypeOfWarn Type);

private:
    QString m_InitialSentence;
    QString m_FinalSentence;
    int m_Shift;

    // Settings
    bool KeepSpaces = false;
    bool KeepSpecialChar = true;

    QList<QString> cmdList = { expPLAY, expOPTIONS };
};
