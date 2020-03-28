#include "JSONPendu.h"
#include <thread>

std::thread lol;

void JSONPendu::Pendu_AddWord(QString Word)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QJsonArray Array;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	Array = PenduObj["Words"].toArray();
	Array.insert(Array.begin(), Word);
	PenduObj["Words"] = Array;

	//______________________________________________________________________
	jsonObj["Pendu"] = PenduObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}

void JSONPendu::Pendu_AddSentence(QString Word)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QList<QString> Array;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	Array = JSONManager::QJsonArrayToQList(PenduObj["Sentences"].toArray());
	Array.insert(Array.end(), Word);

	PenduObj["Sentences"] = JSONManager::QListToQSonArray(Array);

	//______________________________________________________________________
	jsonObj["Pendu"] = PenduObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}

bool JSONPendu::Pendu_RemoveWord(QString Word)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QList<QString> Array;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	Array = JSONManager::QJsonArrayToQList(PenduObj["Words"].toArray());

	if (!Array.contains(Word)) {
		return false;
	}
	while (Array.contains(Word)) {
		Array.removeOne(Word);
	}

	PenduObj["Words"] = JSONManager::QListToQSonArray(Array);

	//______________________________________________________________________
	jsonObj["Pendu"] = PenduObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();

	return true;
}

bool JSONPendu::Pendu_RemoveSentence(QString Word)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QList<QString> Array;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	Array = JSONManager::QJsonArrayToQList(PenduObj["Sentences"].toArray());

	if (!Array.contains(Word)) {
		return false;
	}
	while (Array.contains(Word)) {
		Array.removeOne(Word);
	}

	PenduObj["Sentences"] = JSONManager::QListToQSonArray(Array);

	//______________________________________________________________________
	jsonObj["Pendu"] = PenduObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();

	return true;
}

QString JSONPendu::GetWord()
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QJsonArray Array = {};

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	Array = PenduObj["Words"].toArray();

	//______________________________________________________________________

	jsonFile.close();

	return QListToQString(QJsonArrayToQList(Array));
}

QString JSONPendu::GetSentence()
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QJsonArray Array = {};

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	Array = PenduObj["Sentences"].toArray();

	//______________________________________________________________________

	jsonFile.close();

	return QListToQString(QJsonArrayToQList(Array));
}

void JSONPendu::Pendu_CleanWordsArray()
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QJsonArray Array = {};

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	PenduObj["Words"] = Array;

	//______________________________________________________________________
	jsonObj["Pendu"] = PenduObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}

void JSONPendu::Pendu_CleanSentenceArray()
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue PenduVal;
	QJsonObject PenduObj;

	QJsonArray Array = {};

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	PenduVal = jsonObj.value(QString("Pendu"));
	PenduObj = PenduVal.toObject();
	//______________________________________________________________________

	PenduObj["Sentences"] = Array;

	//______________________________________________________________________
	jsonObj["Pendu"] = PenduObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}
