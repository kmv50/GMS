#ifndef UTIL_H
#define UTIL_H
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonObject>

QVariantMap parseJson(const QString &str);
void BindDataHtmlForm(const QString &token , const QString &value , QString &PhtmlForm);
//Crear una funcion para validar las comillas y demas...

#endif // UTIL_H
