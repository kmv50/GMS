#ifndef EMPRESAS_H
#define EMPRESAS_H
#include <BaseClase.h>

class empresas: public BaseClase
{
public:
    explicit empresas();
    ~empresas();
    virtual QString GetTable();
    virtual QString GetForm(int id);
    virtual bool DeletebyCod(int cod);
    virtual QString GetScript();
protected:
    virtual bool RequestExec();
};

#endif // EMPRESAS_H
