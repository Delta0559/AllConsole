#include "Caesar.h"

Caesar::Caesar() : m_Shift(0), m_InitialSentence(""), m_FinalSentence("")
{
    JSONCaesar().Caesar_GetBoolValue(KeepSpecialChar, JSONCaesar::CaesarBool::KeepSpecialChar);
    JSONCaesar().Caesar_GetBoolValue(KeepSpaces, JSONCaesar::CaesarBool::KeepSpaces);
}

Caesar::~Caesar()
{
}

SubActionManager::Action Caesar::FuncCaesar(QList<QString> args)
{
    QString Str; // The string given
    QList<QString> argsMode;
    bool ok = false;
    QString Answer = expYES;
    SubActionManager::Action Action;

    if (args.contains("-p")) { Caesar().Play(args); }

    do
    {
        qDebug() << "\nChoisisez le mode\n"
            "> ";
        SubActionManager::GetValue(Str);

        argsMode = Str.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if (SubActionManager::if_(argsMode[0], SubActionManager::Statement::Back)) {
            return SubActionManager::Action::Back;
        }
        if (SubActionManager::if_(argsMode[0], SubActionManager::Statement::Quit)) {
            return SubActionManager::Action::Quit;
        }
        if (SubActionManager::if_(argsMode[0], SubActionManager::Statement::Info)) {
            Caesar().GiveInfo(Caesar::TypeOfInfo::Global);
            continue;
        }

        for (QString var : cmdList) {
            if (argsMode[0] == var) {
                ok = true;
                if (STATE(argsMode[0], SubActionManager::Statement::Play)) {
                    Action = Caesar().Play(args);
                }
                if (STATE(argsMode[0], SubActionManager::Statement::Options)) {
                    Action = Caesar().Options();
                }
            }
        }

        if (!ok) {
            qDebug() << "Commande non valide\n";
        }

    } while (!STATE(Answer, SubActionManager::Statement::No));

    return SubActionManager::Action::Finish;
}

SubActionManager::Action Caesar::Play(QList<QString> args)
{
    QString Str; // The string given
    QString Answer = expYES; // Yes or No (restart)
    bool ok = false;
    SubActionManager::Action Action;
    do
    {
        if (STATE(Answer, SubActionManager::Statement::Yes)) // While the user want to continue AND it is a correct answer (Oui || Non)
        {
        checkpoint1:
            qDebug() << "La/les phrase(s) : ";
            SubActionManager::GetValue(Str); // Fill the Str (string) with the sentence;

            BACK_AND_QUIT_CHECK(Str)

            m_InitialSentence = Str;

            /*--------------------------------------------------------------------------------------------*/

            do
            {
                qDebug() << "Le decalage : ";
                SubActionManager::GetValue(Str);

                if (STATE(Str, SubActionManager::Statement::Back)) {
                    goto checkpoint1;
                }

                QUIT_CHECK(Str)

                ok = SubActionManager::POM_ConvertStringToIntValue(Str, m_Shift);
                if (!ok) {
                    GiveWarn(Caesar::TypeOfWarn::NumbersOnly);
                }
            } while (!ok);

            m_FinalSentence = Caesar::Translation(m_InitialSentence, m_Shift); // Make the translation

            qDebug().noquote() << "\nResultat : " << m_FinalSentence.toUtf8() << "\n\n"; // Print it

            qDebug() << "Recommencer ? (Non || Oui) : ";
            SubActionManager::GetValue(Answer);
        }

        while (!STATE(Answer, SubActionManager::Statement::No) && !STATE(Answer, SubActionManager::Statement::Yes)) {
            qDebug() << "Reponse non valable (Oui || Non) !\n"
                "> ";
            SubActionManager::GetValue(Answer);
        }

    } while (!STATE(Answer, SubActionManager::Statement::No)); // While the user want to continue

    return SubActionManager::Action::Finish;
}

SubActionManager::Action Caesar::Options()
{
    QString Str;
    QString Answer;
    QList<QString> argsMode;
    SubActionManager::Action Action = SubActionManager::Action::NoAction;

    qDebug() << "\n <Caesar> [Options] \n> ";

    do
    {
        SubActionManager::GetValue(Str);

        argsMode = Str.split(QRegExp("\\s+"));

        if (STATE(argsMode[0], SubActionManager::Statement::Info)) {
            Caesar().GiveInfo(Caesar::TypeOfInfo::Settings);
        }

        if (argsMode[0] == "1") {
            Action = Caesar().ManageOptions(Str, Caesar::TypeOfOptions::KeepSpaces);
        }
        if (argsMode[0] == "2") {
            Action = Caesar().ManageOptions(Str, Caesar::TypeOfOptions::KeepSpecialChar);
        }
        else {
            GiveWarn(Caesar::TypeOfWarn::OneOrTwo);
        }

    } while (!STATE(Action, SubActionManager::Statement::_Backing));

    return SubActionManager::Action::Finish;
}

SubActionManager::Action Caesar::ManageOptions(QString Str, TypeOfOptions Type)
{
    bool ok;

    switch (Type) {

    case Caesar::TypeOfOptions::KeepSpaces:

        Caesar().GiveInfo(Caesar::TypeOfInfo::AskKeepSpaces);

        do {
            SubActionManager::GetValue(Str);

            if (STATE(Str, SubActionManager::Statement::Yes)) {
                KeepSpaces = true;
                ok = true;
                JSONCaesar().Caesar_ReplaceBoolValue(KeepSpaces, JSONCaesar::CaesarBool::KeepSpaces);
            }

            if (STATE(Str, SubActionManager::Statement::No)) {
                KeepSpaces = false;
                ok = true;
                JSONCaesar().Caesar_ReplaceBoolValue(KeepSpaces, JSONCaesar::CaesarBool::KeepSpaces);
            }

            else {
                ok = false;
                GiveWarn(TypeOfWarn::YesOrNo);
            }

        } while (!ok);
        break;

    case Caesar::TypeOfOptions::KeepSpecialChar:

        Caesar().GiveInfo(Caesar::TypeOfInfo::AskKeepSpecialChar);


        do {
            SubActionManager::GetValue(Str);

            if (STATE(Str, SubActionManager::Statement::Yes)) {
                KeepSpecialChar = true;
                ok = true;
                JSONCaesar().Caesar_ReplaceBoolValue(KeepSpecialChar, JSONCaesar::CaesarBool::KeepSpecialChar);
            }


            if (STATE(Str, SubActionManager::Statement::No)) {
                KeepSpaces = false;
                ok = true;
                JSONCaesar().Caesar_ReplaceBoolValue(KeepSpecialChar, JSONCaesar::CaesarBool::KeepSpecialChar);
            }


            else {
                ok = false;
                GiveWarn(Caesar::TypeOfWarn::YesOrNo);
            }

        } while (!ok);
        break;

    }

    return SubActionManager::Action::Finish;
}

QString Caesar::Translation(QString _Str, int _Number)
{
    QString Str = _Str.toUtf8();
    QString alphabet("abcdefghijklmnopqrstuvwxyz");
    QString alphabetMAJ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    QString AllNum("0123456789");
    QString finalString("");

    int index;
    int index3;

    for (int i(0); i < Str.size(); i++)
    {
        index3 = Caesar::LoopInAString(Str, i);

        index = alphabet.indexOf(Str[index3]);

        if (index != -1) {
            index3 = Caesar::LoopInAString(alphabet, index + _Number);
            finalString.append(alphabet[index3]);
            continue;
        }
        else {
            index = alphabetMAJ.indexOf(Str[index3]);

            if (index != -1) {
                index3 = Caesar::LoopInAString(alphabet, index + _Number);
                finalString.append(alphabetMAJ[index3]);
                continue;
            }

            else {
                index = AllNum.indexOf(Str[i]);
                if (index != -1) {
                    index3 = Caesar::LoopInAString(AllNum, index + _Number);
                    finalString.append(AllNum[index3]);
                }
                else {
                    if (KeepSpecialChar) {
                        finalString.append(Str[i]);
                    }
                    else {
                        if (Str[i] == " ") {
                            if (KeepSpaces) {
                                finalString.append(Str[i]);
                            }
                        }
                    }
                }
            }
        }
    }
    return finalString;
}

int Caesar::LoopInAString(QString _Str, int _num)
{
    int j = 0;

    for (int i(0); i < _num; i++)
    {
        if (j == _Str.size() - 1) {
            j = 0;
        }
        j++;
    }
    return _Str.indexOf(_Str[j]); // = Index of _Str[i], but without overloop
}

void Caesar::GiveInfo(TypeOfInfo Type)
{
    SubActionManager::ChangeTextColor(SubActionManager::Color::Info);

    switch (Type)
    {
    case Caesar::TypeOfInfo::Global:

        _Print("Caesar Cipher, abrege Caesar, est une technique de cryptage de texte premierement utilise"
            " par Julius Caesar lui meme qui consiste a decaller chaque lettre du mot un certain nombre"
            " de fois par rapport a sa place dans l'alphabet.\n"
            "Example : abc devient bcd, comme 123 devient 234 si on le decalle de 1\n\n"
            "Les commandes disponibles sont :\n"
            "    - play       (pour commencer)\n"
            "    - !options   (pour definir ses preferances)\n\n");
        break;

    case Caesar::TypeOfInfo::Settings:
        _Print("Voici tout les parametres disponibles :\n"
            " 1 - Conserver les espaces\n"
            " 2 - Conserver les caracteres speciaux (virgules, point ...)\n");
        break;

    case Caesar::TypeOfInfo::AskKeepSpaces:
        SubActionManager::ChangeTextColor(SubActionManager::Color::Navy);
        qDebug() << "Voulez vous activer l'option \"Conserver les espaces\" ? ";
        break;

    case Caesar::TypeOfInfo::AskKeepSpecialChar:
        SubActionManager::ChangeTextColor(SubActionManager::Color::Navy);
        qDebug() << "Voulez vous activerl'option \"Conserver les caracteres speciaux\" ?";
        break;
    }

    SubActionManager::ResetTextColor();
}

void Caesar::GiveWarn(TypeOfWarn Type)
{
    switch (Type)
    {
    case Caesar::TypeOfWarn::OneOrTwo:
        SubActionManager::InputTextWithColor(SubActionManager::Color::Warning,
            "Seules les values \"1\" et \"2\" sont autorisees !");
        break;

    case Caesar::TypeOfWarn::YesOrNo:
        SubActionManager::InputTextWithColor(SubActionManager::Color::Warning,
            "Reponse non valide, seuls \"Oui\" et \"Non\" sont autorises\n"
            "> ");
        break;

    case Caesar::TypeOfWarn::NumbersOnly:
        SubActionManager::InputTextWithColor(SubActionManager::Color::Red, "Seuls les chiffres sont autorises !\n");
        break;
    default:
        break;
    }
}
