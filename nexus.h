#ifndef NEXUS_H
#define NEXUS_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <vector>
#include <QVariant>
#include <QDebug>

using namespace std;
typedef vector<QString>  TableTitle;
struct FCaller
{
    QString name;
    QString value;
    QString ccs;
    vector<int> data;
};
typedef vector<FCaller> FCallerVector;
typedef vector<QVariant> Nexus_Row;
typedef vector<Nexus_Row> Nexus_Table;
class Nexus
{
private:
    TableTitle titulos;
    FCallerVector botones;
    bool Open();
    void CloseConexion();
    QString lastError;
    QSqlDatabase *db;
    QSqlQuery *query;
    QString esquema;
    QString host;
    QString usuario;
    QString password;
public:
    Nexus();
    void addTitle(QString th){titulos.push_back(th);}
    void addBoton(FCaller boton){botones.push_back(boton);}
    QString GetHtmlTable(QString procedure );
    bool ejecute(QString strQuery);
    QString GetLastError(){return lastError;}
    Nexus_Row GetOneRow(QString procedure);
    Nexus_Table GetDAtaTable(QString procedure);
    QString GetComboBox(QString procedure, int codSelect = -1);
};

#endif // NEXUS_H
