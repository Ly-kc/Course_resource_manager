#include<QDir>
#include <QApplication>
#include<QFileDialog>
#include <QDebug>
#include<filterwidget.h>
#include "mainwindow.h"
#include "json/json.h"
#include "datamanager.h"
#include<statchart.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    mw.transfer_files();
    MainWindow* mainwindow = new MainWindow;
    mainwindow->show();
    a.exec();
   delete mainwindow;
    return 0;
}
