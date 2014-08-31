#include "empresas.h"
/*
 * Empresas.html
:Cod_empresa	Cod_empresa
:nombre		txt_Genericos_Nombre
:telefono1      txt_empre_telefono1
:telefono2      txt_empre_telefono2
:web		txt_empre_web
:email		txt_empre_email
:descripcion    txt_empre_descripcion
:Direccion	txt_empre_direccion

g_map
:latitud
:longitud


 */
empresas::empresas()
    :BaseClase()
{
}
empresas::~empresas()
{

}

QString empresas::GetForm(int id)
{
    try{
        LoadFormHTml("html/frames/Empresas.html");
    }catch(QString ex)
    {
        return ex;
    }
    if(id == 0)
    {
        BindDataHtmlForm(":Cod_empresa","0");
        BindDataHtmlForm(":nombre","");
        BindDataHtmlForm(":telefono1","");
        BindDataHtmlForm(":telefono2","");
        BindDataHtmlForm(":web","");
        BindDataHtmlForm(":email","");
        BindDataHtmlForm(":descripcion","");
        BindDataHtmlForm(":Direccion","");
    }
    else
    {

    }
    return html;
}

QString empresas::GetTable()
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


bool empresas::DeletebyCod(int cod)
{

}
//_Cod_empresa int,
//_nombre varchar(50),
//_telefono varchar(20),
//_telefono2 varchar(20),
//_latitud decimal(17,15),
//_longitud decimal(17,15),
//_Direccion varchar(250),
//_email varchar(70),
//_web varchar(250),
//_Descripcion text

bool empresas::RequestExec()
{
  QString querySTR = "call sp_setEmpresas("+JsonObj["Cod"].toString()+",'"+JsonObj["Nombre"].toString()+"','"+JsonObj["Tel1"].toString()+"','"+JsonObj["Tel2"].toString()+"',"+JsonObj["latitud"].toString()+","+JsonObj["longitud"].toString()+",'"+JsonObj["direccion"].toString()+"','"+JsonObj["email"].toString()+"','"+JsonObj["web"].toString()+"','"+JsonObj["description"].toString()+"');";
  sql = new Nexus;
  if(!sql->ejecute(querySTR))
  {
    delete sql;
    lastError = sql->GetLastError();
    return false;
  }
  delete sql;
  return true;
}
QString empresas::GetScript()
{
    try {
        return LoadScript("html/Scripts/JSEmpresa.js");
    } catch (QString ex) {
        return ex;
    }
}
