#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout* whole_layout = new QHBoxLayout;
    QVBoxLayout* left_layout = new QVBoxLayout;
    QVBoxLayout* middle_layout = new QVBoxLayout;
    QVBoxLayout* right_layout = new QVBoxLayout;

    file_tree = new FileTree;
    file_tree->setMinimumWidth(140);
    filter_widget = new FilterWidget;
    transfer_button = new QPushButton;
    transfer_button->setText("中转文件");

    left_layout->addWidget(transfer_button);
    left_layout->addWidget(file_tree,11);
    middle_layout->addWidget(filter_widget,5);
    middle_layout->addStretch(1);


    whole_layout->addLayout(left_layout,2);
    whole_layout->addLayout(middle_layout,5);
    whole_layout->addLayout(right_layout);
    //whole_layout->addWidget(filter_widget,1);
    //mainwindow不能直接setlayout
    central_widget = new QWidget;
    central_widget->setLayout(whole_layout);
    this->setCentralWidget(central_widget);

    connect(transfer_button,&QPushButton::clicked,this,&MainWindow::trans_files);
}

void MainWindow::trans_files()
{
    mw.transfer_files();
    file_tree->flush();
    filter_widget->show_result();
}

MainWindow::~MainWindow()
{
    delete ui;
}


