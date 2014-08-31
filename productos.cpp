#include "productos.h"

Productos::Productos()
    :BaseClase()
{

}
Productos::~Productos()
{

}
/*
:Cod_Producto
:nombre
:compra
:venta
:cb_categoria
:marcaSelected
:cb_medida
:proveedoresData
 */

QString Productos::GetTable()
{
   sql = new Nexus;
   sql->addTitle("Codigo");
   sql->addTitle("Nombre");
   sql->addTitle("Compra");
   sql->addTitle("Venta");
   sql->addTitle("Mostrar");
   sql->addTitle("Borrar");

   FCaller boton;
   boton.ccs = "botonir";
   boton.name = "";
   boton.value = "";
   boton.data.push_back(0);
   sql->addBoton(boton);

   FCaller boton2;
   boton2.ccs = "botoneliminar";
   boton2.name = "";
   boton2.value = "";
   boton2.data.push_back(0);
   try
   {
    QString tb  = sql->GetHtmlTable("");
    delete sql;
    return tb;
   }catch(QString ex)
   {
       delete sql;
       return ex;
   }
}

QString Productos::getMarcasTable(QString filter)
{

}

QString Productos::GetForm(int id)
{

}

bool Productos::DeletebyCod(int cod)
{

}

bool Productos::RequestExec()
{

}
QString Productos::GetScript()
{
    try {
        return LoadScript("");
    } catch (QString ex) {
        return ex;
    }
}
