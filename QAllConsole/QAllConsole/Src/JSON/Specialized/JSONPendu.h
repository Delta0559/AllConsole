#pragma once

#include "../JSONManager.h"

class JSONPendu : public JSONManager
{
public:
	void Pendu_AddWord(QString Word);
	void Pendu_AddSentence(QString Word);

	bool Pendu_RemoveWord(QString Word);
	bool Pendu_RemoveSentence(QString Word);

	QString GetWord();
	QString GetSentence();

	void Pendu_CleanWordsArray();
	void Pendu_CleanSentenceArray();
};
