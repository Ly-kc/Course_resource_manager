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
#include<QStackedLayout>
#include<filterwidget.h>
#include<addfiledialog.h>
#include<filetree.h>
#include<noteswidget.h>
#include<QBoxLayout>
#include<weblist.h>
#include<statchart.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FilterWidget;
class FileTree;
class NotesWidget;
class WebList;
class StatChart;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private: 
    Ui::MainWindow *ui;
    QHBoxLayout* whole_layout;
    QVBoxLayout* left_layout;
    QVBoxLayout* middle_layout;
    QVBoxLayout* filter_layout;
    QHBoxLayout* function_layout;
    QStackedLayout* right_layout;
    FilterWidget* filter_widget;
    FilterWidget* sub_filter_widget;
    FileTree* file_tree;  //文件树
    QWidget* central_widget; //中部组件
    QPushButton* transfer_button; //转运按钮
    QPushButton* chart_button;
    QPushButton* notes_button;
    QPushButton* course_table_button;
    QPushButton* website_button;
    QPushButton* magic_button;
    WebList* web_list;
    NotesWidget* stikey_notes;
    StatChart* charts;
    int table_num;
    void trans_files();
    void add_table();
    void del_table();
    void show_notes();
    void del_layout(QBoxLayout* p_layout);
    void show_websites();
    void show_charts();
};
#endif // MAINWINDOW_H
