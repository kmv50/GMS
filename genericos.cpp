#include "genericos.h"

Genericos::Genericos()
    :BaseClase()
{

}
Genericos::~Genericos()
{

}

bool Genericos::RequestExec()
{

   QString query = "call sp_setGenerico("+QString::number(idForm)+","+JsonObj["CodGenerico"].toString()+",'"+JsonObj["Nombre"].toString()+"','"+JsonObj["Descripcion"].toString()+"','"+JsonObj["Abre"].toString()+"');";
   sql = new Nexus;
   if(!sql->ejecute(query))
   {
       delete sql;
       lastError = sql->GetLastError();
       return false;
   }
   delete sql;
   return true;
}


QString Genericos::GetTable()
{
    sql = new Nexus;
    sql->addTitle("Codigo");
    sql->addTitle("Nombre");
    sql->addTitle("Abreviacion");
    sql->addTitle("Mostrar");
    sql->addTitle("Borrar");
    FCaller boton;
    boton.ccs = "botonir";
    boton.name = "JGetGenericosbyID";
    boton.value = "";
    boton.data.push_back(0);
    sql->addBoton(boton);


    FCaller boton2;
    boton2.ccs = "botoneliminar";
    boton2.name = "JDeleteGenericosbyID";
    boton2.value = "";
    boton2.data.push_back(0);
    //boton2.data.push_back(1);
    sql->addBoton(boton2);
    try{
        QString tb = sql->GetHtmlTable("call sp_getGenerico("+QString::number(idForm)+",0);");
        delete sql;
        return tb;
    }catch(QString ex)
    {
        delete sql;
        return ex;
    }

}
/*
:nombre
:Descripcion
:abre
*/
QString Genericos::GetForm(int id)
{
  LoadFormHTml("html/frames/Generico.html");
  BindDataHtmlForm(":Titulo",getTitulo());
  if(id == 0)
  {
     BindDataHtmlForm(":Cod_Generico","0");
     BindDataHtmlForm(":nombre","");
     BindDataHtmlForm(":Descripcion","");
     BindDataHtmlForm(":abre","");
  }
  else
  {
      sql = new Nexus;
      Nexus_Row row = sql->GetOneRow("call sp_getGenerico("+QString::number(idForm)+","+QString::number(id)+")");
      BindDataHtmlForm(":Cod_Generico",QString::number(id));
      BindDataHtmlForm(":nombre",row[0].toString());
      BindDataHtmlForm(":Descripcion",row[1].toString());
      BindDataHtmlForm(":abre",row[2].toString());
      delete sql;
  }
  return html;
}

bool Genericos::DeletebyCod(int cod)
{
    sql = new Nexus;
    if(!sql->ejecute("call sp_deleteGenerico("+QString::number(idForm)+","+QString::number(cod)+")"))
    {
        delete sql;
        lastError = sql->GetLastError();
        return false;
    }
    delete sql;
    return true;
}

QString Genericos::getTitulo()
{
   if(CRCategorias == idForm)
       return "Categoria";
   if(CRMarcas == idForm)
       return "Marcas";
   if(CRMedidas == idForm)
       return "Medidas";
   if(CRTipos == idForm)
       return "Tipos";
   return NULL;
}
