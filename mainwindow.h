#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include"QtHeaderFiles.h"
#include<filterwidget.h>
#include<addfiledialog.h>
#include<filetree.h>
#include<noteswidget.h>
#include<QBoxLayout>
#include<weblist.h>
#include<statchart.h>
#include<recent.h>
#include<introwidget.h>
#include "mypushbotton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//class FilterWidget;
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
    FilterWidget* sub_filter_widget = 0;
    FileTree* file_tree;  //文件树
    QWidget* central_widget; //中部组件
    QPushButton* transfer_button; //转运按钮
    //QPushButton* chart_button;
    MyPushButton* chart_button;
    //QPushButton* notes_button;
    MyPushButton* notes_button;
    //QPushButton* website_button;
    MyPushButton* website_button;
    //QPushButton* recent_button;
    MyPushButton* recent_button;
    WebList* web_list;
    NotesWidget* stikey_notes;
    StatChart* charts = 0;
    Recent* recent;
    QMenuBar* head_menu_bar;
    QMenu* settings;
    QMenu* help;
    IntroWidget* introduction;

    int table_num;

    void glob_flush();

    void trans_files();
    void mod_table();
    void add_table();
    void del_table();
    void show_notes();
    void del_right_layout();
    void show_websites();
    void show_charts();
    void show_recent();
    void init_right();
    void action_reflect(QAction* action);
    void show_intro();

    void paintEvent(QPaintEvent *);
};
#endif // MAINWINDOW_H
