#include <QApplication>
#include <QSplashScreen>
#include <mainwindow.h>
//C:\QT\Qt5.3.1\5.3\mingw482_32\plugins\sqldriver
int main(int argc, char *argv[])
{

//    para ver conexion name git remote
//    git pull origin
//    git add *
//    git commit
//    git push origin master
    QApplication a(argc, argv);
    QWebSettings::setMaximumPagesInCache(0);
    QWebSettings::setObjectCacheCapacities(0, 0, 0);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("Splashscreen.jpg"));
    splash->show();
    MainWindow p;
    QTimer::singleShot(2500, splash, SLOT(close()));
    QTimer::singleShot(2500, &p, SLOT(showMaximized()));
   // delete splash;
    return a.exec();
}
