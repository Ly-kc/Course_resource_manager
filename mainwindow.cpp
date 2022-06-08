#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file_tree = new FileTree;
    file_tree->setMinimumWidth(100);
    filter_widget = new FilterWidget;
    QHBoxLayout* whole_layout = new QHBoxLayout;
    QVBoxLayout* left_layout = new QVBoxLayout;
    left_layout->addStretch(1);
    left_layout->addWidget(file_tree,11);
    whole_layout->addLayout(left_layout,0);
    whole_layout->addWidget(filter_widget,1);
    central_widget = new QWidget;
    central_widget->setLayout(whole_layout);
    this->setCentralWidget(central_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


