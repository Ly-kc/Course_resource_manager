#include "introwidget.h"

IntroWidget::IntroWidget(QWidget *parent) : QWidget(parent)
{
    intro_widget = new QWizard(this);
    page1 = new QWizardPage;
    page2 = new QWizardPage;
    page3 = new QWizardPage;

    intro_widget->setWindowTitle("使用向导");

    page1->setTitle("文件转运");
    QLabel* text1 = new QLabel("首先需在左上方的设置菜单中指定中转站文件夹与存储文件夹，\n"
                               "随后点击转运按钮即可将中转站中的文件夹以随后在对话框中\n输入的信息"
                               "（名称、学科，类型、优先级）进行转运，\n即自动在存储文件夹中分类存储。\n"
                               "\n注：若存储文件夹中的文件结构与自动分类不同\n（即subject—type—文件），\n会导致程序界面文件陈列不正常。");
    text1->setWordWrap(true);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(text1);
    page1->setLayout(layout1);

    page2->setTitle("文件筛选");
    QLabel* text2 = new QLabel("中间窗口为文件筛选窗口，支持名称匹配、学科、类型、时间、优先级筛选。\n"
                               "右键某一信息的单元格可显示菜单，包括修改文件该项信息，\n新增筛选窗口（最多两个）与删除新增的筛选窗口。\n点击表头某列可将该列完全显示/部分隐藏。");
    text2->setWordWrap(true);
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(text2);
    page2->setLayout(layout2);

    page3->setTitle("其他功能");
    QLabel* text3 = new QLabel("统计图表:\n"
                               "点击窗口下方统计图表按钮即可展示不同学科文件打开频率比例的饼状图\n"
                               "与最近几日打开文件频率的折线图。"
                               "右侧窗口:\n"
                               "若要隐藏，可在左上方设置菜单中设置。\n"
                               "其中最近打开会展示最近打开的文件，单击即可打开。\n"
                               "备忘便签会显示存放的便签，右键可选择删除或置顶便签。\n"
                               "常用网址即存放网址，左键可打开，右键有删除选项。");
    text3->setWordWrap(true);
    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addWidget(text3);
    page3->setLayout(layout3);

    intro_widget->addPage(page1);
    intro_widget->addPage(page2);
    intro_widget->addPage(page3);

    setStyleSheet("font-family:KaiTi;");

}

void IntroWidget::show_intro()
{
    intro_widget->show();
}
