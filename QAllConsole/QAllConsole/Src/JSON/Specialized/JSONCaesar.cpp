#include "JSONCaesar.h"

void JSONCaesar::Caesar_ReplaceBoolValue(bool ok, CaesarBool type)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue caesarVal;
	QJsonObject caesarObj;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();
	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	caesarVal = jsonObj.value(QString("Caesar"));
	caesarObj = caesarVal.toObject();

	switch (type)
	{
	case CaesarBool::KeepSpaces:
		caesarObj["KeepSpaces"] = ok ? QJsonValue(true) : QJsonValue(false);
		break;

	case CaesarBool::KeepSpecialChar:
		caesarObj["KeepSpecialChar"] = ok ? QJsonValue(true) : QJsonValue(false);
		break;
	}

	jsonObj["Caesar"] = caesarObj;

	jsonDoc.setObject(jsonObj);

	QByteArray jsonData = jsonDoc.toJson();
	jsonFile.write(jsonData);
	jsonFile.close();
}

void JSONCaesar::Caesar_GetBoolValue(bool& ok, CaesarBool type)
{
	QFile jsonFile(PATH_JSON);
	QByteArray text;

	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	QJsonValue caesarVal;
	QJsonObject caesarObj;

	jsonFile.open(QIODevice::OpenModeFlag::ReadWrite);
	text = jsonFile.readAll();
	jsonFile.close();

	jsonDoc = QJsonDocument::fromJson(text);
	jsonObj = jsonDoc.object();

	caesarVal = jsonObj.value(QString("Caesar"));

	caesarObj = caesarVal.toObject();

	switch (type)
	{
	case CaesarBool::KeepSpaces:
		ok = caesarObj.value("KeepSpaces").toBool();
		break;

	case CaesarBool::KeepSpecialChar:
		ok = caesarObj.value("KeepSpecialChar").toBool();
		break;
	}
}