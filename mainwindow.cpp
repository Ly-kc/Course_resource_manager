#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QIcon>
#include <QFont>
#include <QTimer>

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

    QFont font;
    font.setFamily("KaiTi");
    setFont(font);

    file_tree = new FileTree;
    file_tree->setMinimumWidth(140);
    file_tree->setMaximumWidth(160);
    filter_widget = new FilterWidget;
    transfer_button = new QPushButton;
    transfer_button->setText("中转文件");
    //notes_button = new QPushButton;
    notes_button = new MyPushButton;
    notes_button->setText("备忘便签");
    //website_button = new QPushButton;
    website_button = new MyPushButton;
    website_button->setText("常用网址");
    //recent_button = new QPushButton;
    recent_button = new MyPushButton;
    recent_button->setText("最近打开");
    //chart_button = new QPushButton;
    chart_button = new MyPushButton;
    chart_button->setText("学习统计");
    head_menu_bar = this->menuBar();   //---------------------------------------------还有帮助菜单？
    settings = new QMenu("设置");
    settings->addAction("设置中转站");
    settings->addAction("设置存储位置");
    settings->addAction("隐藏右侧窗口");
    help = new QMenu("帮助");
    introduction = new IntroWidget;
    head_menu_bar->addMenu(settings);
    head_menu_bar->addMenu(help);

    left_layout->addWidget(transfer_button);
    left_layout->addWidget(file_tree,11);
    filter_layout->addWidget(filter_widget);
    middle_layout->addLayout(filter_layout,5);
    function_layout->addWidget(chart_button);
    function_layout->addWidget(recent_button);
    function_layout->addWidget(notes_button);
    function_layout->addWidget(website_button);
    middle_layout->addLayout(function_layout);

    whole_layout->addLayout(left_layout,3);
    whole_layout->addLayout(middle_layout,6);
    whole_layout->addStretch(0);
    init_right();

    //mainwindow不能直接setlayout
    central_widget = new QWidget;
    central_widget->setLayout(whole_layout);
    this->setCentralWidget(central_widget);

    connect(transfer_button,&QPushButton::clicked,this,&MainWindow::trans_files);
    connect(filter_widget,&FilterWidget::mod_table_signal,this,&MainWindow::mod_table);
    connect(filter_widget,&FilterWidget::add_table_signal,this,&MainWindow::add_table);
    connect(filter_widget,&FilterWidget::del_table_signal,this,&MainWindow::del_table);
    //connect(chart_button,&QPushButton::clicked,this,&MainWindow::show_charts);
    connect(chart_button,&MyPushButton::clicked,[=](){
        chart_button->zoom1();
        chart_button->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->MainWindow::show_charts();
        });
    });
    //connect(notes_button,&QPushButton::clicked,this,&MainWindow::show_notes);
    connect(notes_button,&MyPushButton::clicked,[=](){
        notes_button->zoom1();
        notes_button->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->MainWindow::show_notes();
        });
    });
    //connect(website_button,&QPushButton::clicked,this,&MainWindow::show_websites);
    connect(website_button,&MyPushButton::clicked,[=](){
        website_button->zoom1();
        website_button->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->MainWindow::show_websites();
        });
    });
    //connect(recent_button,&QPushButton::clicked,this,&MainWindow::show_recent);
    connect(recent_button,&MyPushButton::clicked,[=](){
        recent_button->zoom1();
        recent_button->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->MainWindow::show_recent();
        });
    });
    connect(settings,&QMenu::triggered,this,&MainWindow::action_reflect);
    connect(help,&QMenu::aboutToShow,introduction,&IntroWidget::show_intro);


    setWindowIcon(QIcon(":/images/ico.ico"));

    setWindowTitle("课程资源管理器");

    setWindowOpacity(0.95);

    setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(0,0,0);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    FileTree{\
    font-family:KaiTi;\
    }\
    ");

    transfer_button->setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(255,235,205);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    ");

    notes_button->setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(255,235,205);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    ");

    website_button->setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(255,235,205);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    ");

    recent_button->setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(255,235,205);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    ");

    chart_button->setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(255,235,205);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    ");
}


void MainWindow::action_reflect(QAction *action)
{
    if(action->text() == "设置中转站")
    {
        QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", desktop_path, QFileDialog::ShowDirsOnly);      
        std::string * p_trans_dir = const_cast<std::string *>(&trans_dir);
        if(dirpath!= "") * p_trans_dir = dirpath.toStdString();
        qDebug() << QString::fromStdString(trans_dir);
        glob_flush();
    }
    else if(action->text() == "设置存储位置")
    {
        QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", desktop_path, QFileDialog::ShowDirsOnly);
        std::string * p_glob_dir = const_cast<std::string *>(&glob_dir);
        if(dirpath!= "") * p_glob_dir = dirpath.toStdString();
        qDebug() << QString::fromStdString(glob_dir);
        glob_flush();
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
    qDebug() << QString::fromStdString(trans_dir);
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
    if(charts== 0) charts = new StatChart;
    charts->show();
}

void MainWindow::show_recent()
{
    if(right_layout == 0) init_right();
    right_layout->setCurrentWidget(recent);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainWindow::~MainWindow()
{
    delete web_list;
    delete ui;
}


