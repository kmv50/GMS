#include "util.h"


QVariantMap parseJson(const QString &str)
{
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    if(doc.isNull())
    {
       throw  "Json no reconocido";
    }
    else
       return doc.object().toVariantMap();
}

void BindDataHtmlForm(const QString &token, const QString &value , QString &PhtmlForm)
{
    PhtmlForm.replace(PhtmlForm.indexOf(token),token.size(),value);
}

QString CreateJsonFromQVariantMap(QVariantMap json)
{
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(json));
    return doc.toJson();
}
