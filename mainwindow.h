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
#include<noteswidget.h>

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
    FilterWidget* sub_filter_widget;
    FileTree* file_tree;  //文件树
    QWidget* central_widget; //中部组件
    QPushButton* transfer_button; //转运按钮
    QPushButton* notes_button;
    QPushButton* course_table_button;
    QPushButton* website_button;
    QPushButton* magic_button;
    int table_num;
    void trans_files();
    void add_table();
    void del_table();
};
#endif // MAINWINDOW_H
