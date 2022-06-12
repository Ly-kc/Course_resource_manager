#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table_num = 1;
    QHBoxLayout* whole_layout = new QHBoxLayout;
    QVBoxLayout* left_layout = new QVBoxLayout;
    QVBoxLayout* middle_layout = new QVBoxLayout;
    QHBoxLayout* function_layout = new QHBoxLayout;
    QVBoxLayout* right_layout = new QVBoxLayout;

    file_tree = new FileTree;
    file_tree->setMinimumWidth(140);
    filter_widget = new FilterWidget;
    sub_filter_widget = new FilterWidget;
    transfer_button = new QPushButton;
    transfer_button->setText("中转文件");
    notes_button = new QPushButton;
    notes_button->setText("备忘便签");
    website_button = new QPushButton;
    website_button->setText("常用网址");
    course_table_button = new QPushButton;
    course_table_button->setText("课表");
    magic_button = new QPushButton;
    NotesWidget* stikey_notes = new NotesWidget;
    stikey_notes->setMinimumWidth(200);

    left_layout->addWidget(transfer_button);
    left_layout->addWidget(file_tree,11);
    middle_layout->addWidget(filter_widget,5);
    function_layout->addWidget(notes_button);
    function_layout->addWidget(course_table_button);
    function_layout->addWidget(website_button);
    middle_layout->addLayout(function_layout);
    right_layout->addWidget(stikey_notes);

    whole_layout->addLayout(left_layout,2);
    whole_layout->addLayout(middle_layout,5);
    whole_layout->addLayout(right_layout,3);
    //whole_layout->addWidget(filter_widget,1);
    //mainwindow不能直接setlayout
    central_widget = new QWidget;
    central_widget->setLayout(whole_layout);
    this->setCentralWidget(central_widget);

    connect(transfer_button,&QPushButton::clicked,this,&MainWindow::trans_files);
    connect(filter_widget,&FilterWidget::add_table_signal,this,&MainWindow::add_table);
    connect(filter_widget,&FilterWidget::del_table_signal,this,&MainWindow::del_table);
}

void MainWindow::trans_files()
{
    mw.transfer_files();
    file_tree->flush();
    filter_widget->show_result();
}

void MainWindow::add_table()
{
    qDebug() << "add";
}

void MainWindow::del_table()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}


