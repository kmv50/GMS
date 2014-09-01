#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWebKitWidgets>
#include <QDebug>
#include <NameClase.h>
#include <genericos.h>
#include <empresas.h>
#include <proveedores.h>
#include <util.h>

class MainWindow: public QWebView
{
    Q_OBJECT
public:
    explicit MainWindow(QWebView *parent = 0);
    ~MainWindow();
private:
    QString lastError;
    //QTime timer;
    //timer.start();
    //QString::number(timer.elapsed());
public slots:
    bool Guardar(int id, QString Request);
    QString GetError(){return lastError;}
    QString GetTable(int id, int index = 0, QString request = NULL);
    QString GetForm(int id,int cod);//id para buscar el objeto y cod para ver si la cargo desde el inicio o form nulo
    bool Borrar(int id , int cod);
    QString GetScript(int id);
};

#endif // MAINWINDOW_H
