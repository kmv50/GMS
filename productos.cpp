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
void Productos::procesarRequestTB(QString json)
{
   try{JsonObj = parseJson(json);}catch(QString ex){throw ex;}
}

QString Productos::GetTable()
{
  try{
        if(JsonObj["action"].toInt() == 0)
            return MainTable();
        if(JsonObj["action"].toInt() == 1)
            return MarcasTable(JsonObj["filter"].toString());
        if(JsonObj["action"].toInt() == 2)
            return ProveedoresTable(JsonObj["filter"].toString());
   }catch(QString ex)
   {
      return ex;
   }
   return NULL;
}


QString Productos::MainTable()
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
    boton.name = "getProductoByID";
    boton.value = "";
    boton.data.push_back(0);
    sql->addBoton(boton);

    FCaller boton2;
    boton2.ccs = "botoneliminar";
    boton2.name = "DeleteProductoByID";
    boton2.value = "";
    boton2.data.push_back(0);
    try
    {
     QString tb  = sql->GetHtmlTable("call sp_getProductos(0);");
     delete sql;
     return tb;
    }catch(QString ex)
    {
        delete sql;
        return ex;
    }
}

QString Productos::MarcasTable(QString name)
{
    sql = new Nexus;
    sql->addTitle("Codigo");
    sql->addTitle("Nombre");
    sql->addTitle("Abreviacion");
    sql->addTitle("Usar");
    FCaller boton;
    boton.ccs = "botonir";
    boton.name = "addMarca";
    boton.value = "";
    boton.data.push_back(0);
    boton.data.push_back(1);
    sql->addBoton(boton);
    QString query;
    if(name.isNull())
        query = "call sp_getMarcasModal();";
    else
        query = "call sp_getMarcasModalFilter('"+name+"');";

    try
    {
     QString tb  = sql->GetHtmlTable(query);
     delete sql;
     return tb;
    }catch(QString ex)
    {
        delete sql;
        return ex;
    }

}
QString Productos::ProveedoresTable(QString name)
{
    sql = new Nexus;
    sql->addTitle("Codigo");
    sql->addTitle("Nombre");
    sql->addTitle("Telefono");
    sql->addTitle("Empresa");
    sql->addTitle("Usar");
    FCaller boton;
    boton.ccs = "botonir";
    boton.name = "addProveedor";
    boton.value = "";
    boton.data.push_back(0);
    boton.data.push_back(1);
    sql->addBoton(boton);
    QString query;
    if(name.isNull())
        query = "call sp_getProveedoresModal();";
    else
        query = "call sp_getProveedoresModalFiltro('"+name+"');";

    try
    {
     QString tb  = sql->GetHtmlTable(query);
     delete sql;
     return tb;
    }catch(QString ex)
    {
        delete sql;
        return ex;
    }

}


QString Productos::GetForm(int id)
{
    try{
        LoadFormHTml("html/frames/Productos.html");
    }catch(QString ex)
    {
        return ex;
    }
    sql = new Nexus;
    if(id == 0)
    {
        BindDataHtmlForm(":Cod_Producto","0");
        BindDataHtmlForm(":nombre","");
        BindDataHtmlForm(":compra","");
        BindDataHtmlForm(":venta","");
        BindDataHtmlForm(":cb_categoria",sql->GetComboBox("call sp_CBCategorias();"));//
        BindDataHtmlForm(":marcaSelected","");
        BindDataHtmlForm(":cb_medida",sql->GetComboBox("call sp_CBMedidas();"));//
        BindDataHtmlForm(":proveedoresData","");//aqui se pone feo para el load
    }
    else
    {
       Nexus_Row row =  sql->GetOneRow("call sp_getProveedor("+QString::number(id)+");");
       BindDataHtmlForm(":Cod_Producto",QString::number(id));
    }

return html;
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
        return LoadScript("html/Scripts/JSProductos.js");
    } catch (QString ex) {
        return ex;
    }
}
