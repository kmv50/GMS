#include "mainwindow.h"

MainWindow::MainWindow(QWebView *parent)
    :QWebView(parent)
{
    setWindowTitle("GMS");
    setContextMenuPolicy(Qt::PreventContextMenu);
#ifdef __linux__
    setUrl(QString("file://"+QDir::currentPath()+"/html/GMS/MainWindow.html"));
#elif _WIN32
    setUrl(QString("file://"+QDir::currentPath()+"\html\GMS\MainWindow.html"));
#else
#error Sistema Operativo no soportado
#endif
    //setUrl(QString("file:///var/www/html/PhpProject1/public_html/GMS/MainWindow.html"));
    page()->mainFrame()->addToJavaScriptWindowObject("QT", this);
}
MainWindow::~MainWindow()
{

}


bool MainWindow::Guardar(int id, QString Request)
{
    try{
    switch (id) {
    case CRMarcas: case CRCategorias: case CRMedidas: case CRTipos: {
       Genericos *obj = new Genericos;
       obj->setIdForm(id);
       obj->SetJsonRequest(Request);
       delete obj;
    }break;
    case CREmpresas:{
        empresas *obj = new empresas;
        obj->SetJsonRequest(Request);
        delete obj;
    }break;
    default: return false;  break;
    }
    }catch(QString ex)
    {
        lastError = ex;
        return false;
    }
    return true;
}

QString MainWindow::GetTable(int id, int index, QString request)
{
    QString tableHtml;
    switch (id) {
    case CRMarcas: case CRCategorias: case CRMedidas: case CRTipos: {
       Genericos *obj = new Genericos;
       obj->setIdForm(id);
       tableHtml = obj->GetTable();
       delete obj;
    }break;

    case CREmpresas:
    {
        empresas *obj = new empresas;
        tableHtml = obj->GetTable();
        delete obj;
    }break;

    default: return "Clase no encontrada";  break;
    }
    return tableHtml;
}

QString MainWindow::GetForm(int id, int cod)
{
    QString form;
    switch (id) {
    case CRMarcas: case CRCategorias: case CRMedidas: case CRTipos: {
       Genericos *obj = new Genericos;
       obj->setIdForm(id);
       form = obj->GetForm(cod);
       delete obj;
    }break;
    case CREmpresas:{
        empresas *obj = new empresas;
        form = obj->GetForm(cod);
        delete obj;
    }break;
    default: return "Clase no encontrada";  break;
    }
    return form;
}

bool MainWindow::Borrar(int id, int cod)
{
    switch (id) {
    case CRMarcas: case CRCategorias: case CRMedidas: case CRTipos: {
       Genericos *obj = new Genericos;
       obj->setIdForm(id);
       if(!obj->DeletebyCod(cod))
       {
            lastError = obj->getLAstError();
            delete obj;
            return false;
       }
    }break;

    case CREmpresas: {
       empresas *obj = new empresas;
       if(!obj->DeletebyCod(cod))
       {
            lastError = obj->getLAstError();
            delete obj;
            return false;
       }
    }break;

    default: return false;  break;
    }
    return true;
}

QString MainWindow::GetScript(int id)
{
    QString script;
    switch (id) {
    case CRMarcas: case CRCategorias: case CRMedidas: case CRTipos: {
       Genericos *obj = new Genericos;
       script = obj->GetScript();
       delete obj;
    }break;
    case CREmpresas:{
        empresas *obj = new empresas;
        script = obj->GetScript();
        delete obj;
    }break;
    default: return "alert('Error no se encontro la clase referente')";  break;
    }
    return script;
}
