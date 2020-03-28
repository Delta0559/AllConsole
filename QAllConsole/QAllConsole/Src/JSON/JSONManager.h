#pragma once

#include <QFile>
#include <QString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define PATH_DATA "C:/Users/Guillaume Vanleene/Downloads/Data"
#define PATH_JSON PATH_DATA"/Data.json"

class JSONManager
{
public:

	JSONManager();
	~JSONManager();

protected:
	virtual void Setup();

	virtual void SetupPrimaryObject();

public:

	static QList<QString> QJsonArrayToQList(QJsonArray _array);
	static QJsonArray QListToQSonArray(QList<QString> _list);
	static QString QListToQString(QList<QString> _list);

	void SA_AssignColorId(int colorId);
	int SA_GetColorId();
};
