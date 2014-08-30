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
    QString getMarcasTable();
protected:
    virtual bool RequestExec();
};

#endif // PRODUCTOS_H
