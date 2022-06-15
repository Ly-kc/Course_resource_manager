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
    right_layout = new QStackedLayout;

    file_tree = new FileTree;
    file_tree->setMinimumWidth(140);
    filter_widget = new FilterWidget;
    transfer_button = new QPushButton;
    transfer_button->setText("中转文件");
    notes_button = new QPushButton;
    notes_button->setText("备忘便签");
    website_button = new QPushButton;
    website_button->setText("常用网址");
    course_table_button = new QPushButton;
    course_table_button->setText("课表");
    chart_button = new QPushButton;
    chart_button->setText("学习统计");
    magic_button = new QPushButton;
    stikey_notes = new NotesWidget;
    stikey_notes->setMinimumWidth(200);
    web_list = new WebList;
    charts = new StatChart;

    left_layout->addWidget(transfer_button);
    left_layout->addWidget(file_tree,11);
    filter_layout->addWidget(filter_widget);
    middle_layout->addLayout(filter_layout,5);
    function_layout->addWidget(chart_button);
    function_layout->addWidget(notes_button);
    function_layout->addWidget(course_table_button);
    function_layout->addWidget(website_button);
    middle_layout->addLayout(function_layout);
    right_layout->addWidget(stikey_notes);
    right_layout->addWidget(web_list);

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
    connect(chart_button,&QPushButton::clicked,this,&MainWindow::show_charts);
    connect(notes_button,&QPushButton::clicked,this,&MainWindow::show_notes);
    connect(website_button,&QPushButton::clicked,this,&MainWindow::show_websites);
}

void MainWindow::trans_files()
{
    mw.transfer_files();
    file_tree->flush();
    filter_widget->show_result();
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
        table_num --;
    }
}

void MainWindow::del_layout(QBoxLayout *p_layout) //只能深两层layout--------------------------可用于隐藏页面？
{
    QBoxLayout* m_pMainLayout = p_layout;
    while(m_pMainLayout->count())
    {
        QWidget *pWidget=m_pMainLayout->itemAt(0)->widget();
        if (pWidget)
        {
            pWidget->setParent (NULL);
            m_pMainLayout->removeWidget(pWidget);
            delete pWidget;
        }
        else
        {
            QLayout *pLayout=m_pMainLayout->itemAt(0)->layout();
            if (pLayout)
            {
                while(pLayout->count())
                {
                    QWidget *pTempWidget=pLayout->itemAt(0)->widget();
                    if (pTempWidget)
                    {
                        pTempWidget->setParent (NULL);
                        pLayout->removeWidget(pTempWidget);
                        delete pTempWidget;
                    }
                    else
                    {
                        pLayout->removeItem(pLayout->itemAt(0));
                    }
                }
            }
            m_pMainLayout->removeItem(m_pMainLayout->itemAt(0));
        }
    }
  delete p_layout;
}

void MainWindow::show_notes()
{
    right_layout->setCurrentWidget(stikey_notes);
}

void MainWindow::show_websites()
{
    right_layout->setCurrentWidget(web_list);
}

void MainWindow::show_charts()
{
    charts->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


