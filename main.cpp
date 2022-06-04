#include "mainwindow.h"
#include<QDir>
#include <QApplication>
#include<QFileDialog>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile temp_info("temp_info.txt");
    temp_info.open(QIODevice::WriteOnly);
    QDataStream writeInfoStr(&temp_info);
    AddFileDialog dialog("233.txt","D:/code",writeInfoStr);
    dialog.show();
//    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", ".");

//    MainWindow w(mFolderPath);
//    w.show();
    return a.exec();
}
