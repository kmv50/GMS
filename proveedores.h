#ifndef PROVEEDORES_H
#define PROVEEDORES_H
#include <BaseClase.h>

class proveedores: public BaseClase
{
public:
    explicit proveedores();
    ~proveedores();
    virtual QString GetTable();
    virtual QString GetForm(int id);
    virtual bool DeletebyCod(int cod);
    virtual QString GetScript();
protected:
    virtual bool RequestExec();
};

#endif // PROVEEDORES_H
