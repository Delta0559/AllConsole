#include "SubActionManager.h"


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void SubActionManager::funcQuit()
{
    
}

void SubActionManager::funcClean()
{
#if defined(Q_OS_WIN)
    QProcess::execute("CLS");

#else
    QProcess::execute("clear");
#endif
}

bool SubActionManager::POM_ConvertStringToIntValue(QString _Str, int& _intValue)
{
    QString StrNumber("");

    for (int i(0); i < _Str.size(); i++)
    {
        if (_Str[i] == '0') { StrNumber.append("0"); }
        if (_Str[i] == '1') { StrNumber.append("1"); }
        if (_Str[i] == '2') { StrNumber.append("2"); }
        if (_Str[i] == '3') { StrNumber.append("3"); }
        if (_Str[i] == '4') { StrNumber.append("4"); }
        if (_Str[i] == '5') { StrNumber.append("5"); }
        if (_Str[i] == '6') { StrNumber.append("6"); }
        if (_Str[i] == '7') { StrNumber.append("7"); }
        if (_Str[i] == '8') { StrNumber.append("8"); }
        if (_Str[i] == '9') { StrNumber.append("9"); }
    }

    if (StrNumber == "") { return false; }

    _intValue = StrNumber.toInt();
    return true;
}

void SubActionManager::GetValue(QString& Str) //test
{
    QTextStream qcin(stdin);

    Str = qcin.readLine();
}

bool SubActionManager::if_(QString Str, SubActionManager::Statement State)
{
    switch (State) {

    case SubActionManager::Statement::Caesar:
        if (Str.toLower() == "caesar") return true;
        break;
    case SubActionManager::Statement::POM:
        if (Str.toLower() == "pom") return true;
        break;
    case SubActionManager::Statement::Pendu:
        if (Str.toLower() == "pendu") return true;
        break;
    case SubActionManager::Statement::Yes:
        if (Str.toLower() == "oui" ||
            Str.toLower() == "yes")
            return true;
        break;
    case SubActionManager::Statement::No:
        if (Str.toLower() == "non" || Str.toLower() == "no") return true;
        break;
    case SubActionManager::Statement::_Answer:
        if (STATE(Str.toLower(), SubActionManager::Statement::Yes) ||
            STATE(Str.toLower(), SubActionManager::Statement::No))
            return true;
        break;
    case SubActionManager::Statement::Quit:
        if (Str.toLower() == "quit") return true;
        break;
    case SubActionManager::Statement::Back:
        if (Str.toLower() == "back" || Str.toLower() == "b") return true;
        break;
    case SubActionManager::Statement::Options:
        if (Str.toLower() == "!options") return true;
        break;
    case SubActionManager::Statement::Info:
        if (Str.toLower() == "info") return true;
        break;
    case SubActionManager::Statement::Clear:
        if (Str.toLower() == "clear") return true;
        break;
    case SubActionManager::Statement::Play:
        if (Str.toLower() == "play") return true;
        break;
    case SubActionManager::Statement::Input:
        if (Str.toLower() == "input") return true;
        break;
    case SubActionManager::Statement::Cancel:
        if (Str.toLower() == "input") return true;
        break;
    case SubActionManager::Statement::Show:
        if (Str.toLower() == "show") return true;
        break;
    case SubActionManager::Statement::Remove:
        if (Str.toLower() == "remove") return true;
        break;
    case SubActionManager::Statement::Word:
        if (Str.toLower() == "word" ||
            Str.toLower() == "words")
            return true;
        break;
    case SubActionManager::Statement::Sentence:
        if (Str.toLower() == "sentence" ||
            Str.toLower() == "sentences")
            return true;
        break;
    }

    return false;
}

bool SubActionManager::if_(SubActionManager::Action Action, SubActionManager::Statement State)
{
    switch (State) {

    case SubActionManager::Statement::_Backing:
        if (Action == SubActionManager::Action::Quit ||
            Action == SubActionManager::Action::Back)
            return true;
        break;

    default:
        _Print("Own : Erreur, Action enum ne peut posseder une autre valeur");
        return false;
    }
}

void SubActionManager::ChangeTextColor(SubActionManager::Color _Color, int _ColorId) // ColorId to put the value, not the enum
{
    int ColorId = 0; // ColorId to determinate to which id correspond which colors (var required to register to .json)

    switch (_Color)
    {
    case SubActionManager::Color::Default:
        ColorId = 15;
        break;
    case SubActionManager::Color::Navy:
        ColorId = 1;
        break;
    case SubActionManager::Color::Info: // Same as Green
    case SubActionManager::Color::Green:
        ColorId = 2;
        break;
    case SubActionManager::Color::Warning: // Same as Red
    case SubActionManager::Color::Red:
        ColorId = 4;
        break;
    case SubActionManager::Color::Grey:
        ColorId = 8;
        break;
    case SubActionManager::Color::ClearBlue:
        ColorId = 9;
        break;
    case SubActionManager::Color::ClearGreen:
        ColorId = 10;
        break;
    case SubActionManager::Color::SkyBleu:
        ColorId = 11;
        break;
    case SubActionManager::Color::Orange:
        ColorId = 12;
        break;
    case SubActionManager::Color::Purple:
        ColorId = 13;
        break;
    case SubActionManager::Color::Beige:
        ColorId = 14;
        break;
    case SubActionManager::Color::Null:
        if (_ColorId != NULL) {
            SetConsoleTextAttribute(hConsole, _ColorId);
            JSONManager().SA_AssignColorId(_ColorId);
            return;
        }
        else { return; }
    }
    SetConsoleTextAttribute(hConsole, ColorId);
    JSONManager().SA_AssignColorId(ColorId);
}

void SubActionManager::ResetTextColor()
{
    SubActionManager().ChangeTextColor(SubActionManager::Color::Default);
}
