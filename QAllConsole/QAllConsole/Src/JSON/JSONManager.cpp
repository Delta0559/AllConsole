#include "JSONManager.h"
#include <QDir>

JSONManager::JSONManager()
{
	Setup();
}

JSONManager::~JSONManager()
{
}

void JSONManager::Setup()
{
	if (!QDir(PATH_DATA).exists())
	{
		QDir().mkpath(PATH_DATA);
	}

	if (!QFile(PATH_JSON).exists())
	{
		SetupPrimaryObject();
	}
}

void JSONManager::SetupPrimaryObject()
{
	QFile jsonFile(PATH_JSON);
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	jsonObj = jsonDoc.object();

	QJsonObject pomObj;

	QJsonObject caesarObj;
	caesarObj.insert("KeepSpaces", false);
	caesarObj.insert("KeepSpecialChar", false);

	QJsonObject penduObj;
	QJsonArray arrWord;
	QJsonArray arrSentence;
	penduObj.insert("Words", arrWord);
	penduObj.insert("Sentences", arrSentence);

	QJsonObject subActionObj;
	subActionObj.insert("ColorId", 15);

	jsonObj.insert("POM", pomObj);
	jsonObj.insert("Caesar", caesarObj);
	jsonObj.insert("Pendu", penduObj);
	jsonObj.insert("SA", subActionObj);

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}

QList<QString> JSONManager::QJsonArrayToQList(QJsonArray _array)
{
	QList<QString> List;

	for (QJsonValue i : _array) {
		List.append(i.toString());
	}

	return List;
}

QJsonArray JSONManager::QListToQSonArray(QList<QString> _list)
{
	QJsonArray JsonArray;
	
	for (QString i : _list) {
		JsonArray.append(i);
	}

	return JsonArray;
}

QString JSONManager::QListToQString(QList<QString> _list)
{
	QString Str;
	for (QString var : _list) {
		Str.append(var);
	}
	return Str;
}

void JSONManager::SA_AssignColorId(int colorId)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue SAVal;
	QJsonObject SAObj;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	SAVal = jsonObj.value(QString("SA"));
	SAObj = SAVal.toObject();

	SAObj["ColorId"] = QJsonValue(colorId);

	jsonObj["SA"] = SAObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}

int JSONManager::SA_GetColorId()
{
	int colorId;
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue SAVal;
	QJsonObject SAObj;

	jsonFile.open(QIODevice::OpenModeFlag::ReadOnly);
	text = jsonFile.readAll();
	jsonFile.close();

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	SAVal = jsonObj.value(QString("SA"));
	SAObj = SAVal.toObject();

	colorId = SAObj["ColorId"].toInt();

	return colorId;
}
