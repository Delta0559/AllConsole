#include "POM.h"

POM::POM()
{
}

POM::~POM()
{
}

SubActionManager::Action POM::FuncPlusOuMoins(QList<QString> args)
{
    QString StrInput = "";
    QString StrRestart = "";

    int HigherNumber = -1;
    int LowerNumber = -1;
    int HiddenNumber = -1;
    int InputNumber = -1;

    int compteur = 0;
    bool ok = true;

    SubActionManager::Action Action;

checkpoint1:
    do // Restarting point
    {
        do {
            qDebug() << "Veuillez choisir le plus petit nombre : ";
            SubActionManager::GetValue(StrInput);

            if (STATE(StrInput, SubActionManager::Statement::Info)) {
                POM::POM_GiveInformation(POM::TypeOfInfo::LowerNum);
                continue;
            }
            if (STATE(StrInput, SubActionManager::Statement::Back)) {
                Action = SubActionManager::Action::Back;
                return Action;
            }
            if (STATE(StrInput, SubActionManager::Statement::Quit)) {
                Action = SubActionManager::Action::Quit;
                return Action;
            }

            ok = SubActionManager::POM_ConvertStringToIntValue(StrInput, LowerNumber);
            if (!ok) { POM::POM_PrintErrorMessageInt(); }

        } while (SubActionManager::if_(StrInput, SubActionManager::Statement::Info)
            || StrInput == ""
            || !ok);

    checkpoint2:

        StrInput.clear();
        ok = false;

        do {
            qDebug() << "Veuillez choisir le plus grand nombre : ";
            SubActionManager::GetValue(StrInput);

            if (STATE(StrInput, SubActionManager::Statement::Info)) {
                POM::POM_GiveInformation(POM::TypeOfInfo::HigherNum);
                continue;
            }
            if (STATE(StrInput, SubActionManager::Statement::Back)) {
                goto checkpoint1;
            }
            if (STATE(StrInput, SubActionManager::Statement::Quit)) {
                Action = SubActionManager::Action::Quit;
                return Action;
            }

            ok = SubActionManager::POM_ConvertStringToIntValue(StrInput, HigherNumber);
            if (!ok) { POM::POM_PrintErrorMessageInt(); continue; }

            if (HigherNumber < LowerNumber) { POM::POM_PrintErrorMessageLowHight(); continue; }

        } while (STATE(StrInput, SubActionManager::Statement::Info)
            || StrInput == ""
            || !ok);

        POM::POM_RandomNumber(LowerNumber, HigherNumber, HiddenNumber);

        qDebug() << "Quel est le nombre mystere : ";
cpAskForHiddenNum:
        do {
            SubActionManager::GetValue(StrInput);

            if (STATE(StrInput, SubActionManager::Statement::Info)) {
                POM::POM_GiveInformation(POM::TypeOfInfo::General);
            }
            if (STATE(StrInput, SubActionManager::Statement::Back)) {
                goto checkpoint2;
            }
            if (STATE(StrInput, SubActionManager::Statement::Quit)) {
                Action = SubActionManager::Action::Quit;
                return Action;
            }

            ok = SubActionManager::POM_ConvertStringToIntValue(StrInput, InputNumber);
            if (!ok) {
                qDebug() << "Vous devez donner un nombre !";
                goto cpAskForHiddenNum;
            }

            if (InputNumber < HiddenNumber) {
                qDebug() << "C'est plus ! ";
            }
            if (InputNumber > HiddenNumber) {
                qDebug() << "C'est moins ! ";
            }

            compteur++;
        } while (HiddenNumber != InputNumber);

        qDebug() << "Bien joue ! Tu as trouve le nombre en " << compteur << " essaies !\n"
            "Recommencer ? (Oui | Non) : ";

        SubActionManager::GetValue(StrRestart);

        compteur = 0;

        while (!STATE(StrRestart, SubActionManager::Statement::_Answer)) // For uncorrect answer
        {
            SubActionManager::InputTextWithColor(SubActionManager::Color::Red, "Seul les reponses \"Oui\" et \"Non\" sont acceptes : ");
            SubActionManager::GetValue(StrRestart);
        }
    } while (!STATE(StrRestart, SubActionManager::Statement::Yes));

    return SubActionManager::Action::Finish;
}

bool POM::POM_RandomNumber(int _intLowest, int _intHighest, int& _intResult)
{
    if (_intLowest > _intHighest) {
        return false;
    }

    QRandomGenerator RandomEng;
    _intResult = RandomEng.bounded(_intLowest, _intHighest);
    return true;
}

void POM::POM_GiveInformation(POM::TypeOfInfo Type)
{
    SubActionManager::ChangeTextColor(SubActionManager::Color::Green);

    switch (Type)
    {
    case POM::TypeOfInfo::General:

        qDebug() << "\nLe jeu du plus ou moins est une extension de ce programme :\n"
            "Il vous demandera de choisir 2 nombres, et de trouver un nombre choisir aleatoirement "
            "par la machine entre ces deux la.\n\n";

        SubActionManager::ResetTextColor();

    case POM::TypeOfInfo::HigherNum:
        qDebug() << "\nVous devez donner ici un nombre, positif comme negatif, qui sera le nombre avec la valeur maximal"
            " les deux que vous entrerez.\n";

        SubActionManager::ChangeTextColor(SubActionManager::Color::Red);
        qDebug() << "ATTENTION : N'inserez que des chiffres ! Le nombre doit aussi etre plus petit que le nombre minimal.\n\n";
        SubActionManager::ChangeTextColor(SubActionManager::Color::Green);
        break;

    case POM::TypeOfInfo::LowerNum:
        qDebug() << "\nVous devez donner ici un nombre, positif comme negatif, qui sera le nombre avec la valeur minimal "
            "les deux que vous entrerez.\n"
            "\"back\" vous ammenerez au choix precedant.\n";

        SubActionManager::ChangeTextColor(SubActionManager::Color::Red);
        qDebug() << "ATTENTION : N'inserez que des chiffres ! Le nombre doit aussi etre plus grand que le nombre maximal.\n\n";
        SubActionManager::ChangeTextColor(SubActionManager::Color::Green);
        break;
    }

    SubActionManager::ResetTextColor();
}

void POM::POM_PrintErrorMessageInt()
{
    SubActionManager::ChangeTextColor(SubActionManager::Color::Red);

    qDebug() << "Seuls les chiffres sont autorises !\n";

    SubActionManager::ChangeTextColor(SubActionManager::Color::Default);
}

void POM::POM_PrintErrorMessageLowHight()
{
    qDebug() << "Ce nombre ci doit etre plus grand que le precedant.\n";
}
