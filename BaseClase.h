#ifndef BASECLASE_H
#define BASECLASE_H
#include <nexus.h>
#include <util.h>
#include <QDebug>
#include <fstream>

using namespace std;

class BaseClase
{
public:
    BaseClase();
    virtual ~BaseClase();
    virtual QString GetTable() = 0;
    virtual QString GetForm(int id) = 0;
    virtual bool DeletebyCod(int cod) =0;
    void SetJsonRequest(const QString &str);
    QString getLAstError(){return lastError;}
protected:
    Nexus *sql;
    QString lastError;
    QString html;//contine el html que se carga con LoadFormHTml y  se modifica con BindDataHtmlForm
    QVariantMap JsonObj;
    void LoadFormHTml(const char * path_file);
    void BindDataHtmlForm(const QString &token , const QString &value);
    virtual bool RequestExec() = 0;
};

#endif // BASECLASE_H
