#include "filterwidget.h"

FilterWidget::FilterWidget(QWidget *parent) : QWidget(parent)
{
    whole_layout = new QVBoxLayout;
    head_layout = new QHBoxLayout;
    table_layout = new QHBoxLayout;
    combo_layout = new QHBoxLayout;
    file_table = new QTableWidget(20,5);
    table_layout->addWidget(file_table,10);
    file_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽
  //  table_layout->addStretch(1);
    filter_button = new QPushButton;
    filter_button->setText("筛选");
    name_edit = new QLineEdit;
    name_edit->setMinimumWidth(100);
    name_edit->setMaximumWidth(150);
    name_edit->setPlaceholderText("文件名...");
    sub_filter = new QComboBox;
    time_filter= new QComboBox;
    type_filter= new QComboBox;
    prior_filter= new QComboBox;
//    sub_filter->setMinimumSize(QSize(60,30));   //width height
//    filter_area= new QScrollArea;
//    filter_area->setMaximumHeight(200);
//    QGridLayout* head_layout = new QGridLayout;
//    head_layout->addWidget(filter_button,0,0,1,1);
//    head_layout->addWidget(name_edit,0,1,1,1);
//    head_layout->addLayout(combo_layout,0,2,1,2);
    head_layout->addWidget(filter_button);
    head_layout->addWidget(name_edit);
    head_layout->addLayout(combo_layout);
//    QGroupBox *pGroupBox = new QGroupBox;
//    filter_area->setLayout(combo_layout);
    combo_layout->addWidget(sub_filter);
    combo_layout->addWidget(type_filter);
    combo_layout->addWidget(time_filter);
    combo_layout->addWidget(prior_filter);
    head_layout->addStretch(1);
    whole_layout->addLayout(head_layout);
    whole_layout->addLayout(table_layout);
    init_combo();
    init_result();
    this->setLayout(whole_layout);
    //connect();
}

void FilterWidget::init_combo()
{
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return true;});
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        CourseFile file = *i;
        if(!subjects.contains(file.get_subject()))
        {
            subjects.append(file.get_subject());
        }
        if(!types.contains(file.get_type()))
        {
            types.append(file.get_type());
        }
    }
    sub_filter->addItems(subjects);
    type_filter->addItems(types);
    QStringList priority;
    priority << "all" << ">=1" << ">=2" << ">=3";
    QStringList times;
    times << "今日" << "昨日" << "三天内";
    prior_filter->addItems(priority);
    time_filter->addItems(times);
}

void FilterWidget::init_result()   //双击打开~~~~~~
{
//    file_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return true;});
    QStringList heads;
    heads << "文件名"<< "学科" << "类型" << "上次时间" << "路径";
    file_table->setHorizontalHeaderLabels(heads);
    QTableWidgetItem* info_item;
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        int row = i - files.begin();
        if(row > 19) break;
        CourseFile file = *i;
        info_item = new QTableWidgetItem(file.get_name());
        file_table->setItem(row,0,info_item);
        info_item = new QTableWidgetItem(file.get_subject());
        file_table->setItem(row,1,info_item);
        info_item = new QTableWidgetItem(file.get_type());
        file_table->setItem(row,2,info_item);
        info_item = new QTableWidgetItem(file.get_time().toString("yyyy/MM/dd HH:mm:ss"));
        file_table->setItem(row,3,info_item);
        info_item = new QTableWidgetItem(file.get_path());
        file_table->setItem(row,4,info_item);
//        QWidgetItem file_item()
//                setItem(int row, int column, QTableWidgetItem *item)setColumnWidth(int column, int width)
    }
}
