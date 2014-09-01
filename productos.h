#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#include <BaseClase.h>

class Productos: public BaseClase
{
public:
    explicit Productos();
    ~Productos();
    virtual QString GetTable();
    virtual QString GetForm(int id);
    virtual bool DeletebyCod(int cod);
    virtual QString GetScript();
    void procesarRequestTB(QString json);
protected:
    virtual bool RequestExec();
private:
    QString MainTable();
    QString MarcasTable(QString name);
    QString ProveedoresTable(QString name);
};

#endif // PRODUCTOS_H
