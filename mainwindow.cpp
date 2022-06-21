#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table_num = 1;
    whole_layout = new QHBoxLayout;
    left_layout = new QVBoxLayout;
    middle_layout = new QVBoxLayout;
    filter_layout = new QVBoxLayout;
    function_layout = new QHBoxLayout;

    file_tree = new FileTree;
    file_tree->setMinimumWidth(140);
    file_tree->setMaximumWidth(160);
    filter_widget = new FilterWidget;
    sub_filter_widget = 0;
    transfer_button = new QPushButton;
    transfer_button->setText("中转文件");
    notes_button = new QPushButton;
    notes_button->setText("备忘便签");
    website_button = new QPushButton;
    website_button->setText("常用网址");
    recent_button = new QPushButton;
    recent_button->setText("最近打开");
    chart_button = new QPushButton;
    chart_button->setText("学习统计");
    charts = new StatChart;
    head_menu_bar = this->menuBar();   //---------------------------------------------还有帮助菜单？
    settings = new QMenu("设置");
    settings->addAction("设置路径");
    settings->addAction("隐藏右侧窗口");
    help = new QMenu("帮助");
    head_menu_bar->addMenu(settings);
    head_menu_bar->addMenu(help);

    left_layout->addWidget(transfer_button);
    left_layout->addWidget(file_tree,11);
    filter_layout->addWidget(filter_widget);
    middle_layout->addLayout(filter_layout,5);
    function_layout->addWidget(chart_button);
    function_layout->addWidget(notes_button);
    function_layout->addWidget(recent_button);
    function_layout->addWidget(website_button);
    middle_layout->addLayout(function_layout);

    whole_layout->addLayout(left_layout,2);
    whole_layout->addLayout(middle_layout,5);
    init_right();

    //mainwindow不能直接setlayout
    central_widget = new QWidget;
    central_widget->setLayout(whole_layout);
    this->setCentralWidget(central_widget);

    connect(transfer_button,&QPushButton::clicked,this,&MainWindow::trans_files);
    connect(filter_widget,&FilterWidget::mod_table_signal,this,&MainWindow::mod_table);
    connect(filter_widget,&FilterWidget::add_table_signal,this,&MainWindow::add_table);
    connect(filter_widget,&FilterWidget::del_table_signal,this,&MainWindow::del_table);
    connect(chart_button,&QPushButton::clicked,this,&MainWindow::show_charts);
    connect(notes_button,&QPushButton::clicked,this,&MainWindow::show_notes);
    connect(website_button,&QPushButton::clicked,this,&MainWindow::show_websites);
    connect(recent_button,&QPushButton::clicked,this,&MainWindow::show_recent);
    connect(settings,&QMenu::triggered,this,&MainWindow::action_reflect);
}

void MainWindow::action_reflect(QAction *action)
{
    if(action->text() == "设置路径")
    {

    }
    else if(action->text() == "隐藏右侧窗口")
    {
        del_right_layout();
    }
}

void MainWindow::glob_flush(){
   file_tree->flush();
   filter_widget->show_result();
   if(sub_filter_widget) sub_filter_widget->show_result();
   recent->refresh();
}

void MainWindow::trans_files()
{

    mw.transfer_files();
    glob_flush();
}

void MainWindow::mod_table(){
    glob_flush();
}

void MainWindow::add_table()
{
    if(table_num == 1)
    {
        sub_filter_widget = new FilterWidget;
        connect(sub_filter_widget,&FilterWidget::del_table_signal,this,&MainWindow::del_table);
        filter_layout->addWidget(sub_filter_widget);
        table_num ++;
    }

}

void MainWindow::del_table()
{
    if(table_num == 2)
    {
        delete sub_filter_widget;
        sub_filter_widget = 0;
        table_num --;
    }
}

void MainWindow::init_right()
{
    right_layout = new QStackedLayout;
    stikey_notes = new NotesWidget;
    stikey_notes->setMinimumWidth(200);
    web_list = new WebList(this);
    recent = new Recent(this);
    right_layout->addWidget(recent);
    right_layout->addWidget(stikey_notes);
    right_layout->addWidget(web_list);
    whole_layout->addLayout(right_layout,3);
}

void MainWindow::del_right_layout()
{
    for(int i = right_layout->count(); i >= 0; i--)
    {
         QWidget* widget = right_layout->widget(i);
         right_layout->removeWidget(widget);
         widget->deleteLater();
    }
    delete right_layout;
    right_layout = 0;
}

void MainWindow::show_notes()
{
    if(right_layout == 0) init_right();
    right_layout->setCurrentWidget(stikey_notes);
}

void MainWindow::show_websites()
{
    if(right_layout == 0) init_right();
    right_layout->setCurrentWidget(web_list);
}

void MainWindow::show_charts()
{
    charts->show();
}

void MainWindow::show_recent()
{
    if(right_layout == 0) init_right();
    right_layout->setCurrentWidget(recent);
}

MainWindow::~MainWindow()
{
    delete web_list;
    delete ui;
}


