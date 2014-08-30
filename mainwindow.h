#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWebKitWidgets>
#include <QDebug>
#include <NameClase.h>
#include <genericos.h>
#include <util.h>

class MainWindow: public QWebView
{
    Q_OBJECT
public:
    explicit MainWindow(QWebView *parent = 0);
    ~MainWindow();
private:
    QString lastError;
    QTime timer;
    //timer.start();
    //QString::number(timer.elapsed());
public slots:
    bool Guardar(int id, QString Request);
    QString GetError(){return lastError;}
    QString GetTable(int id);
    QString GetForm(int id,int cod);//id para buscar el objeto y cod para ver si la cargo desde el inicio o form nulo
    bool Borrar(int id , int cod);

};

#endif // MAINWINDOW_H
