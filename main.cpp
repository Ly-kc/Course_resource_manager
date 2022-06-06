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

    QFile temp_info("temp_info.txt");
    temp_info.open(QIODevice::ReadWrite);
    QDataStream writeInfoStr(&temp_info),readInfoStr(&temp_info);
//    FileTreeWindow fw("");
//    fw.show();
    AddFileDialog dialog("233.txt","D:/code",writeInfoStr);
    dialog.show();
//    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", ".");

//    MainWindow w(mFolderPath);
//    w.show();
    auto files=cfm.filter_file();
    for(auto f:files) qDebug()<<f;
    return a.exec();
}
