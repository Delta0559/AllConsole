#include "ComManager.h"
#include "ComManager.h"

ComManager::ComManager()
{
}

ComManager::~ComManager()
{
}

void ComManager::Menu()
{
    QString Str = "";

    bool ok = false;

    qDebug().noquote() << "Programme multi-fonctions. Plus d'info en faisant " + QString(expINFO) + " \n";

    while (!STATE(Str, SubActionManager::Statement::Quit))
    {
        while (!ok)
        {
            qDebug() << "> ";
            SubActionManager::GetValue(Str);



            QList<QString> args = Str.split(" ", QString::SkipEmptyParts);

            switch (ComManager::FromStringToType(args))
            {
            case SubActionManager::Action::Quit:
                return SubActionManager::funcQuit();
            case SubActionManager::Action::Error:
            default:
                ok = false;
                qDebug() << "\nMenu : \n";
                break;
            }
        }
    }
}

void ComManager::Info()
{
    SubActionManager::ChangeTextColor(SubActionManager::Color::Green);

    qDebug() << "\nDans ce programme, vous avez toutes sortes de micro - programmes integres tel que : \n"
        "- Le jeu du plus ou moins {" + QString(expPOM) + "}\n"
        "- L'encryptage de texte Caesar Cipher (decalage par rapport a l'aphabet) {" + QString(expCAESAR) + "}\n"
        "- Le jeu du Pendu, avec banque de donne modulable {" + QString(expPENDU) + "}\n\n";
    SubActionManager::ChangeTextColor(SubActionManager::Color::SkyBleu);
    qDebug() << "Pour pouvoir utiliser chacune de ces fonctions, vous devez entrer le mot cle mis en accolade, soit :\n"
        "    - " + QString(expPOM) + "        (Plus Ou Moins)\n"
        "    - " + QString(expCAESAR) + "     (Caesar Cipher encrypatge)\n"
        "    - " + QString(expPENDU) + "      (jeu du pendu)\n"
        "    - " + QString(expQUIT) + "       (pour quitter l'appli) ";
    SubActionManager::InputTextWithColor(SubActionManager::Color::Navy, "(UTILISABLE PARTOUT)\n");
    SubActionManager::ChangeTextColor(SubActionManager::Color::SkyBleu);

    qDebug() << "    - " + QString(expBACK) + " (pour revenir en arriere) ";
    SubActionManager::InputTextWithColor(SubActionManager::Color::Navy, "(UTILISABLE PARTOUT)\n\n");
    SubActionManager::ChangeTextColor(SubActionManager::Color::Green);
    qDebug() << "Certains prefixent raccourci existent, tel que -p qui vous met directement dans le mode play"
        " du jeu.\n";
    SubActionManager::ChangeTextColor(SubActionManager::Color::Orange);
    qDebug() << QString(expCAESAR) + " -p    ";
    SubActionManager::ChangeTextColor(SubActionManager::Color::Purple);
    qDebug() << "  =  " + QString(expCAESAR) + "->play\n";
    SubActionManager::ChangeTextColor(SubActionManager::Color::Orange);
    qDebug() << QString(expPENDU) + " -ins ";
    SubActionManager::InputTextWithColor(SubActionManager::Color::Purple, "[...]");
    qDebug() << "  =  " + QString(expPENDU) + " -> insert ";
    SubActionManager::InputTextWithColor(SubActionManager::Color::Purple, "[...]");
    qDebug() << "\n\n";

    SubActionManager::ResetTextColor();
}

SubActionManager::Action ComManager::FromStringToType(QList<QString> args)
{

    if (SubActionManager::if_(args[0], SubActionManager::Statement::Quit))
    {
        return ComManager::CheckFor(args, ComManager::Events::Quit);
    }
    if (SubActionManager::if_(args[0], SubActionManager::Statement::Back))
    {
        return ComManager::CheckFor(args, ComManager::Events::Back);
    }
    if (SubActionManager::if_(args[0], SubActionManager::Statement::Info))
    {
        return ComManager::CheckFor(args, ComManager::Events::Info);
    }
    if (SubActionManager::if_(args[0], SubActionManager::Statement::Clear))
    {
        return ComManager::CheckFor(args, ComManager::Events::Clear);
    }
    if (SubActionManager::if_(args[0], SubActionManager::Statement::POM))
    {
        return ComManager::CheckFor(args, ComManager::Events::PlusOuMoins);
    }
    if (SubActionManager::if_(args[0], SubActionManager::Statement::Caesar))
    {
        return ComManager::CheckFor(args, ComManager::Events::Caesar);
    }
    if (SubActionManager::if_(args[0], SubActionManager::Statement::Pendu))
    {
        return ComManager::CheckFor(args, ComManager::Events::Pendu);
    }
    else
    {
        qDebug() << "Commande non valide (!info pour plus d'aide).\n";
        return SubActionManager::Action::Error;
    }
}

SubActionManager::Action ComManager::CheckFor(QList<QString> args, ComManager::Events _Type)
{
    switch (_Type)
    {
    case ComManager::Events::Quit:
        SubActionManager::funcQuit();
        return SubActionManager::Action::Quit;

    case ComManager::Events::Back:
        qDebug() << "Pour quitter le programme, preferez \"quit\".\n";
        return SubActionManager::Action::Finish;

    case ComManager::Events::Info:
        ComManager().Info();
        return SubActionManager::Action::Finish;

    case ComManager::Events::Clear:
        SubActionManager::funcClean();
        return SubActionManager::Action::Finish;

    case ComManager::Events::Caesar:
        switch (Caesar().FuncCaesar(args))
        {
        case SubActionManager::Action::Finish:
            return SubActionManager::Action::Finish;

        case SubActionManager::Action::Back:
            return SubActionManager::Action::Back;

        case SubActionManager::Action::Quit:
            return SubActionManager::Action::Quit;

        case SubActionManager::Action::Error:
            qDebug() << "Own : An error occured while leaving\n";
            return SubActionManager::Action::Error;
        }
        break;

    case ComManager::Events::PlusOuMoins:
        switch (POM().FuncPlusOuMoins(args))
        {
        case SubActionManager::Action::Finish:
            return SubActionManager::Action::Finish;

        case SubActionManager::Action::Back:
            return SubActionManager::Action::Back;

        case SubActionManager::Action::Quit:
            return SubActionManager::Action::Quit;

        case SubActionManager::Action::Error:
            qDebug() << "An error occured while leaving\n";
            return SubActionManager::Action::Error;
        }
        break;

    case ComManager::Events::Pendu:
        switch (Pendu().funcPendu(args, 1))
        {
        case SubActionManager::Action::Finish:
            return SubActionManager::Action::Finish;

        case SubActionManager::Action::Back:
            return SubActionManager::Action::Back;

        case SubActionManager::Action::Quit:
            return SubActionManager::Action::Quit;

        case SubActionManager::Action::Error:
            qDebug() << "An error occured while leaving\n";
            return SubActionManager::Action::Error;
        }
        break;
    }
}
