#ifndef GENERICOS_H
#define GENERICOS_H
#include <BaseClase.h>
#include <NameClase.h>

class Genericos: public BaseClase
{
public:
    explicit Genericos();
    ~Genericos();
    virtual bool RequestExec();
    virtual QString  GetTable();
    virtual QString GetForm(int id);
    virtual bool DeletebyCod(int cod);
    void setIdForm(int id){this->idForm = id;}
private:
    QString getTitulo();
    int idForm;
};

#endif // GENERICOS_H
