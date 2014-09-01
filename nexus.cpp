#include "nexus.h"

Nexus::Nexus()
{
    esquema = "GMS";
    host = "127.0.0.1";
    usuario = "root";
    password = "sempron";
}
bool Nexus::Open()
{
    db = new QSqlDatabase;
    *db = QSqlDatabase::addDatabase("QMYSQL","gmsConection");
    db->setHostName(host);
    db->setDatabaseName(esquema);
    db->setUserName(usuario);
    db->setPassword(password);
    if(!db->open())
    {
        lastError = db->lastError().text();
        return false;
    }
    return true;
}
void Nexus::CloseConexion()
{
   db->close();
   *db = QSqlDatabase();
   db->removeDatabase("gmsConection");
   delete db;
}

QString Nexus::GetHtmlTable(QString procedure)
{
    QString tableHtml;
    if(!Open())
    {
        CloseConexion();
        throw lastError;
    }
    query = new QSqlQuery(*db);
    if(!query->exec(procedure))
    {
        lastError = query->lastError().text();
        CloseConexion();
        delete query;
        throw lastError;
    }
    tableHtml = "<table class=\"bordered\"><thead>";
    for(unsigned int i = 0 ; i < titulos.size() ; i++)
        tableHtml += "<th>"+titulos[i]+"</th>";
    tableHtml += "</thead>";
    titulos.clear();

    while (query->next())
    {
        tableHtml += "<tr>";
        for(int i = 0 ; i < query->record().count() ; i++)
        {
            tableHtml += "<td>"+query->value(i).toString()+"</td>";
        }
        if(botones.size() != 0)
        {
            for(unsigned int i = 0 ; i < botones.size() ; i++)
            {
                QString dataFunction;
                for(unsigned int x = 0 ; x < botones[i].data.size() ; x++)
                    dataFunction += "'"+query->value(botones[i].data[x]).toString()+"',";
                dataFunction.remove(dataFunction.length()-1,1);
                tableHtml += "<td><input type=\"button\" value=\""+botones[i].value+"\" class=\""+botones[i].ccs+"\" onclick=\""+botones[i].name+"("+dataFunction+")\"<td>";
            }
        }
        tableHtml += "</tr>";
    }
    botones.clear();
    query->clear();
    delete query;
    CloseConexion();
    return tableHtml+="</table>";
}

bool Nexus::ejecute(QString strQuery)
{

    if(!Open())
    {
        CloseConexion();
        return false;
    }
    query = new QSqlQuery(*db);
    if(!query->exec(strQuery))
    {
        lastError = query->lastError().text();
        delete query;
        CloseConexion();
        return false;
    }

    query->clear();
    delete query;

    CloseConexion();
    return true;
}

Nexus_Row Nexus::GetOneRow(QString procedure)
{

    if(!Open())
    {
        CloseConexion();
        throw lastError;
    }
    query = new QSqlQuery(*db);
    if(!query->exec(procedure))
    {
        lastError = query->lastError().text();
        CloseConexion();
        delete query;
        throw lastError;
    }
    query->next();
    Nexus_Row row;
    for(int i = 0 ; i < query->record().count() ; i++)
         row.push_back(query->value(i));

    query->clear();
    delete query;
    CloseConexion();
    return row;
}

Nexus_Table Nexus::GetDAtaTable(QString procedure)
{

    if(!Open())
    {
        CloseConexion();
        throw lastError;
    }
    query = new QSqlQuery(*db);
    if(!query->exec(procedure))
    {
        lastError = query->lastError().text();
        CloseConexion();
        delete query;
        throw lastError;
    }
    Nexus_Table table;
    while(query->next())
    {
    Nexus_Row row;
    for(int i = 0 ; i < query->record().count() ; i++)
         row.push_back(query->value(i));
    table.push_back(row);
    row.clear();
    }
    query->clear();
    delete query;
    CloseConexion();
    return table;
}

QString Nexus::GetComboBox(QString procedure,int codSelect)
{
    if(!Open())
    {
        CloseConexion();
        throw lastError;
    }
    query = new QSqlQuery(*db);
    if(!query->exec(procedure))
    {
        lastError = query->lastError().text();
        query->clear();
        delete query;
        CloseConexion();
        throw lastError;
    }
    QString cb;
    if(codSelect == -1)
    {
       cb +="<option value='-1' selected >Seleccione un item</option>";
       while (query->next())
           cb +="<option value='"+query->value(0).toString()+"'>"+query->value(1).toString()+"</option>";
    }
    else
    {
       cb +="<option value='-1'>Seleccione un item</option>";
       while (query->next()) {
           if(query->value(0).toInt() == codSelect)
             cb +="<option value='"+query->value(0).toString()+"' selected >"+query->value(1).toString()+"</option>";
           else
             cb +="<option value='"+query->value(0).toString()+"'>"+query->value(1).toString()+"</option>";
       }
    }
    query->clear();
    delete query;
    CloseConexion();
    return  cb;
}
