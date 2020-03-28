#include "Pendu.h"

Pendu::Pendu()
{
}

Pendu::~Pendu()
{
}

SubActionManager::Action Pendu::Play(QList<QString> args, int index)
{
    QString Answer;
chAskForType:
    _Print("Voulez vous jouer avec des mots, ou avec des phrases ?\n");
    SubActionManager::GetValue(Answer);

    if (STATE(Answer, SubActionManager::Statement::Info)){
        _Print("Dans ce mode, vous pouvez jouer au pendu avec des mots ou des phrases (a votre choix) que vous aurez vous-meme renseigner dans"
            " la partie Manage Data");
    }
    

    if (STATE(Answer, SubActionManager::Statement::Word)) {
        QVector<int> Discovered;

        QString Str = JSONPendu().GetWord();
        if (Str.isEmpty()) {
            _Print("Le BDD de mots est vide !");
            goto chAskForType;
        }

        QStringToUnderScore(&Str);
        
        _Print("\n\n" + Str + "\n> ");
    }
    if (STATE(Answer, SubActionManager::Statement::Sentence)){
        QString Str = JSONPendu().GetSentence();
    }
    else {

    }
    
    _Print("\n");

    return SubActionManager::Action::Finish;
}

SubActionManager::Action Pendu::Remove(QList<QString> args, int index)
{
    return SubActionManager::Action();
}

SubActionManager::Action Pendu::Add(QList<QString> args, int index)
{
    return SubActionManager::Action();
}

void Pendu::QStringToUnderScore(QString* Str, QVector<int> Discovered)
{
    QStringView copy(*Str);

    for (int var: Discovered) {
        Str[var] = copy[var];
    }
}

void Pendu::QStringToUnderScore(QString* Str)
{
    int i(1);
    for (QString::iterator it = Str->begin(); it != Str->end(); i++) {
        if (i % 2 != 0) { *it = '_'; it++; }
        else { Str->insert(i, ' '); }
    }
}

SubActionManager::Action Pendu::funcPendu(QList<QString> args, int index)
{
    SubActionManager::Action Action;
    QString Str;
    QString Answer = expYES;
    bool ok = false;

    qDebug() << "\nBienvenue dans le jeux du pendu ! (!info pour plus d'info)\n";

    do
    {
        qDebug() << "> ";
        SubActionManager::GetValue(Str);

        QList<QString> args = Str.split(' ');

        if (STATE(Str, SubActionManager::Statement::Back)) {
           return SubActionManager::Action::Back;
        }
        if (STATE(Str, SubActionManager::Statement::Quit)) {
            return SubActionManager::Action::Quit;
        }
        if (STATE(Str, SubActionManager::Statement::Info)) {
            InformationType Type = InformationType::general;
            GiveInformation(Type);
        }


        for (QString var : cmdList) {
            if (STATE(var, SubActionManager::Statement::Play)) {
                Play(args, 2);
                ok = true;
            }
            if (STATE(var, SubActionManager::Statement::Input)) {
                ok = true;
            }
            if (STATE(var, SubActionManager::Statement::Cancel)) {
                ok = true;
            }
            if (STATE(var, SubActionManager::Statement::Show)) {
                ok = true;
            }
            if (STATE(var, SubActionManager::Statement::Remove)) {
                ok = true;
            }
        }

        if (!ok) { qDebug() << "Commande non valide (!info pour plus d'aide)\n"; }

    } while (STATE(Answer, SubActionManager::Statement::No));

    return SubActionManager::Action::Finish;
}

void Pendu::GiveInformation(InformationType Type)
{
    SubActionManager::ChangeTextColor(SubActionManager::Color::Green);

    switch (Type)
    {
    case Pendu::InformationType::general:
        qDebug() << "\nLe jeux du pendu vous permet de stocker des mots dans un fichier, de les supprimer, "
            "mais surtout de pouvoir faire des pendues avec ces derniers. L'ordinateur en choisira "
            "alatoirement, puis vous l'exposera dans la console.\n\n Les commandes sont : \n";
        SubActionManager::ChangeTextColor(SubActionManager::Color::SkyBleu);
        qDebug() << "- input {mot ...)  (pour ajouter des mots a la base de donnees).\n"
            "- cancel           (pour annuler l'ajout du dernier mot).\n"
            "- show             (pour voir tous les mots enregistres).\n"
            "- remove {mot ...} (pour supprimer un mot).\n"
            "- play             (pour jouer)\n\n";
        SubActionManager::ChangeTextColor(SubActionManager::Color::ClearGreen);
        qDebug() << "Note : si vous voulez inserer ou supprimer plusieurs mots, il faudra les separer avec "
            "des espaces.\nSi vous voulez mettre plusieurs mots en un il faudra les mettres avec des guillemets"
            "\"comme ceci\"\n\n";
        break;
    }

    SubActionManager::ResetTextColor();
}
