#include "proveedores.h"

proveedores::proveedores()
    :BaseClase()
{
}
proveedores::~proveedores()
{

}
QString proveedores::GetTable()
{
    sql = new Nexus;
    sql->addTitle("Codigo");
    sql->addTitle("Nombre");
    sql->addTitle("Telefono");
    sql->addTitle("Nombre");
    sql->addTitle("Mostrar");
    sql->addTitle("Borrar");

    FCaller boton;
    boton.ccs = "botonir";
    boton.name = "getProveedorByID";
    boton.value = "";
    boton.data.push_back(0);
    sql->addBoton(boton);

    FCaller boton2;
    boton2.ccs = "botoneliminar";
    boton2.name = "DeleteProveedorByID";
    boton2.value = "";
    boton2.data.push_back(0);
    sql->addBoton(boton2);

    try
    {
     QString tb  = sql->GetHtmlTable("call sp_getProveedor(0);");
     delete sql;
     return tb;
    }catch(QString ex)
    {
        delete sql;
        return ex;
    }

}

//:Cod_persona
//:cb_empresa
//:telefono1
//:telefono2
//:nombre
//:cedula
//:Direccion

QString proveedores::GetForm(int id)
{
    try{
        LoadFormHTml("html/frames/Proveedores.html");
    }catch(QString ex)
    {
        return ex;
    }
    sql = new Nexus;
    if(id == 0)
    {
        BindDataHtmlForm(":Cod_persona","0");
        BindDataHtmlForm(":cb_empresa",sql->GetComboBox("call sp_getCbEmpresas();"));
        BindDataHtmlForm(":telefono1","");
        BindDataHtmlForm(":telefono2","");
        BindDataHtmlForm(":nombre","");
        BindDataHtmlForm(":email","");
        BindDataHtmlForm(":cedula","");
        BindDataHtmlForm(":Direccion","");
    }
    else
    {
       Nexus_Row row =  sql->GetOneRow("call sp_getProveedor("+QString::number(id)+");");
       BindDataHtmlForm(":Cod_persona",QString::number(id));
       BindDataHtmlForm(":cb_empresa",sql->GetComboBox("call sp_getCbEmpresas();",row[6].toInt()));
       BindDataHtmlForm(":telefono1",row[2].toString());
       BindDataHtmlForm(":telefono2",row[3].toString());
       BindDataHtmlForm(":nombre",row[0].toString());
       BindDataHtmlForm(":email",row[5].toString());
       BindDataHtmlForm(":cedula",row[1].toString());
       BindDataHtmlForm(":Direccion",row[4].toString());
    }

return html;
}


QString proveedores::GetScript()
{
    try {
        return LoadScript("html/Scripts/JSProveedores.js");
    } catch (QString ex) {
        return ex;
    }
}
/*
create procedure sp_setProveedores
(
_Cod_persona int ,
_nombre varchar(50),
_Cedula int,
_telefono varchar(20),
_telefono2 varchar(20),
_Email varchar(70),
_Direccion varchar(300),
_Id_empresa int
)
 */
bool proveedores::RequestExec()
{
    QString querySTR = "call sp_setProveedores("+JsonObj["Cod_persona"].toString()+",'"+JsonObj["nombre"].toString()+"',"+JsonObj["cedula"].toString()+",'"+JsonObj["tel1"].toString()+"','"+JsonObj["tel2"].toString()+"','"+JsonObj["email"].toString()+"','"+JsonObj["direccion"].toString()+"',"+JsonObj["empre"].toString()+");";
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


bool proveedores::DeletebyCod(int cod)
{

}
