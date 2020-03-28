#pragma once

#include <QString>
#include <QTextstream>
#include <Qdebug>
#include <QProcess>

#include <iostream>
#include <future>

#include <windows.h>


#include "Macro.h"
#include "../JSON/JSONManager.h"
class SubActionManager
{
public:
    enum class Color
    {
        Default, Navy, Green, Red, Grey, ClearBlue, ClearGreen, SkyBleu, Orange, Purple, Beige,
        Info, Warning, Null
    };
    enum class Action
    {
        Finish, Back, Quit, Error, NoAction, Continue, Break
    };

    enum class Statement {
        Caesar, POM, Pendu, Yes, No, _Answer, Quit, Back, _Backing, Options, Info, Clear, Play, Input, Cancel, Show, Remove, Word, Sentence
    };

    void static funcQuit();
    void static funcClean();

    bool static POM_ConvertStringToIntValue(QString Str, int& intValue);

    void static GetValue(QString& Str);

    bool static if_(QString Str, SubActionManager::Statement State);
    bool static if_(SubActionManager::Action Action, SubActionManager::Statement State);

    void static ChangeTextColor(SubActionManager::Color _Color, int _ColorId = 0);
    void static ResetTextColor();
    template<typename T> T static InputTextWithColor(SubActionManager::Color _Color, T _TempStr);
};




// That is in the header to avoid some problems with the compiler (that's why it is a inline func)

template<typename T>
T inline SubActionManager::InputTextWithColor(SubActionManager::Color _Color, T _TempStr)
{
    int ColorId = JSONManager().SA_GetColorId();

    SubActionManager::ChangeTextColor(_Color);

    qDebug() << _TempStr;

    SubActionManager::ChangeTextColor(SubActionManager::Color::Null, ColorId);


    return _TempStr;
}
