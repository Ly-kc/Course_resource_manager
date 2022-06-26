#include "introwidget.h"

IntroWidget::IntroWidget(QWidget *parent) : QWidget(parent)
{
    intro_widget = new QWizard(this);
    page1 = new QWizardPage;
    page2 = new QWizardPage;
    page3 = new QWizardPage;

    intro_widget->setWindowTitle("使用向导");

    page1->setTitle("文件转运");
    QLabel* text1 = new QLabel("bulabulabula");
    text1->setWordWrap(true);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(text1);
    page1->setLayout(layout1);

    page2->setTitle("文件筛选");
    QLabel* text2 = new QLabel("bulabulabula");
    text2->setWordWrap(true);
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(text2);
    page2->setLayout(layout2);

    page3->setTitle("其他功能");
    QLabel* text3 = new QLabel("bulabulabula");
    text3->setWordWrap(true);
    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addWidget(text3);
    page3->setLayout(layout3);

    intro_widget->addPage(page1);
    intro_widget->addPage(page2);
    intro_widget->addPage(page3);
}

void IntroWidget::show_intro()
{
    intro_widget->show();
}
