#include "mainwindow.h"
#include "json/json.h"
#include "datamanager.h"
#include<QDir>
#include <QApplication>
#include<QFileDialog>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mw.transfer_files();
//    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", ".");

//    MainWindow w(mFolderPath);
//    w.show();
    auto files=cfm.filter_file();
    for(auto f:files) qDebug()<<f;
    return a.exec();
}
