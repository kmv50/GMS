#include "BaseClase.h"

BaseClase::BaseClase()
{

}
BaseClase::~BaseClase()
{

}

void BaseClase::LoadFormHTml(const char *path_file)
{
    ifstream file;
    file.open(path_file,ios_base::in);
    if(!file.is_open())
        throw QString("El archivo no se a encontrado");
    string htmlCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    html = QString::fromStdString(htmlCode);
}

QString BaseClase::LoadScript(const char *path_file)
{
    ifstream file;
    file.open(path_file,ios_base::in);
    if(!file.is_open())
        throw QString("alert('No se encontro el archivo JS')");
    string ScriptCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return QString::fromStdString(ScriptCode);
}

void BaseClase::BindDataHtmlForm(const QString &token, const QString &value)
{
    html.replace(html.indexOf(token),token.size(),value);
}


void BaseClase::SetJsonRequest(const QString &str)
{
    try{
     JsonObj = parseJson(str);
    }catch(QString ex)
    {
       throw ex;
    }
     if(!RequestExec())
         throw lastError;
}
