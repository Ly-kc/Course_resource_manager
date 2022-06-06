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
//    QFile temp_info("temp_info.txt");
//    temp_info.open(QIODevice::WriteOnly);
//    QDataStream writeInfoStr(&temp_info);
//    AddFileDialog dialog("233.txt","D:/code",writeInfoStr);
    //dialog.show();


//    QFile temp_info("temp_info.txt");
//    temp_info.open(QIODevice::ReadWrite);
//    QDataStream writeInfoStr(&temp_info),readInfoStr(&temp_info);
//    FileTreeWindow fw("");
//    fw.show();
    //    AddFileDialog dialog;
    //    dialog.set_file("hh");
    //    dialog.exec();
    auto file = get_course_file("hh");
    qDebug()<<file;
//    QString mFolderPath = QFileDialog::getExistingDirectory(NULL, "Open Folder", ".");
//    FileTree* myTree = new FileTree;
//    myTree->show();
//    MainWindow w(mFolderPath);
//    w.show();
 //   auto files=cfm.filter_file();
  //  for(auto f:files) qDebug()<<f;
  //  cfm.add_file("C:\\Users\\win\\Desktop\\文档\\ppt模板 - 副本\\北大PPT模版（荷塘绿）.pptx",CourseFile("math","fuck","北大PPT模版（荷塘绿）.pptx"));
    return a.exec();
}
