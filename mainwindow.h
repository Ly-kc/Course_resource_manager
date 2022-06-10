#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include<filterwidget.h>
#include<addfiledialog.h>
#include<filetree.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FilterWidget;
class FileTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FilterWidget* filter_widget;
    FileTree* file_tree;  //文件树
    QWidget* central_widget; //中部组件
    QPushButton* transfer_button; //转运按钮
    void trans_files();
};
#endif // MAINWINDOW_H
