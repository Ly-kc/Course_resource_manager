#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString path,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dir_path = path;
    startup_detect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startup_detect()
{
//    QString curr_path = QDir::currentPath();
//    QDir curr_dir(curr_path);
//    qDebug() << curr_path <<endl;
//    if(!curr_dir.exists("f_info.txt"))
//    {
//        qDebug()<<"不存在该路径"<<endl;
//        curr_dir.mkpath("f_info.txt");
//    }
    QDir dir(dir_path);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    //dir.setNameFilters(QString("*.md").split(";"));
    QStringList mImgNames = dir.entryList();
    QFile file_info("file_info.txt");
    file_info.open(QIODevice::ReadOnly);
    QDataStream readInfoStr(&file_info);
    QMap<QString,FileInfo> files;
    while(!file_info.atEnd())
    {
        FileInfo file;
        readInfoStr >> file.file_name >> file.subject >> file.type >> file.frequency >> file.priority >> file.path;
        files[file.file_name] = file;
    }
    file_info.close();
    QFile temp_info("temp_info.txt");
    temp_info.open(QIODevice::WriteOnly);
    QDataStream writeInfoStr(&temp_info);
    for(int i = 0 ; i < mImgNames.size() ; i ++)
    {
        QString file_name = mImgNames[i];
        if(files.contains(file_name))
        {
            FileInfo file = files[file_name];
            writeInfoStr << file.file_name << file.subject << file.type << file.frequency << file.priority << file.path;
        }
        else
        {
            add_file(file_name,writeInfoStr);
        }
    }
    temp_info.close();
    file_info.remove();
    temp_info.rename("file_info.txt");
}

void MainWindow::add_file(QString file_name,QDataStream& writeInfoStr)
{
//    AddFileDialog* file_dialog = new AddFileDialog(file_name,writeInfoStr,this);

}

