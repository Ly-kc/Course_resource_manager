#include "filterwidget.h"

FilterWidget::FilterWidget(QWidget *parent) : QWidget(parent)
{
    whole_layout = new QVBoxLayout;
    head_layout = new QHBoxLayout;//whole_layout上部
    table_layout = new QHBoxLayout;//whole_layout下部
    combo_layout = new QHBoxLayout;//head_layout右部
    //完成table_layout
//    file_table = new QTableWidget(20,5);//-----------------------------------------------槽函数待添加(右键）
    file_table = new QTableWidget(20,4);
    file_table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    file_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    file_table->setAutoScroll(true);
    table_layout->addWidget(file_table,10);
    file_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//单元格宽度自动拉伸
    file_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    file_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    //完成head
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
    //head_layout->addWidget(filter_button);
    head_layout->addWidget(name_edit);
    head_layout->addLayout(combo_layout);
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
    //connect(filter_button,&QPushButton::clicked,this,&FilterWidget::show_result);
    connect(name_edit,&QLineEdit::editingFinished,this,&FilterWidget::show_result);
    connect(sub_filter,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&FilterWidget::show_result);
    connect(type_filter,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&FilterWidget::show_result);
    connect(time_filter,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&FilterWidget::show_result);
    connect(prior_filter,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&FilterWidget::show_result);
    connect(file_table,&QTableWidget::cellClicked,this,&FilterWidget::click_cell_slot);
}

void FilterWidget::init_combo()
{
    vector<CourseFile> files = cfm.filter_file();
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
    sub_filter->addItem("所有学科");
    type_filter->addItem("所有类型");
    sub_filter->addItems(subjects);
    type_filter->addItems(types);
    QStringList priority;
    priority << "所有优先级" << ">=1" << ">=2" << ">=3";
    QStringList times;
    times << "所有时间" << "今日" << "昨日" << "三天内";
    prior_filter->addItems(priority);
    time_filter->addItems(times);
}

void FilterWidget::init_result()//--------------------------------------------------------能否点表头则全显示
{
    vector<CourseFile> files = cfm.filter_file();
    QStringList heads;
    //heads << "文件名"<< "学科" << "类型" << "上次时间" << "路径";
    heads << "文件名"<< "学科" << "类型" << "上次时间";
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
//        info_item = new QTableWidgetItem(file.get_path());
//        file_table->setItem(row,4,info_item);
    }
}

void FilterWidget::show_result()//--------------------------------------------------------时间筛选待完善
{
    QString name = name_edit->text();
    QString subject = sub_filter->currentText();
    QString type = type_filter->currentText();
    int priority = prior_filter->currentIndex();
    auto filter = [&](CourseFile file){
        if(name!="" && name != file.get_name()) return false;
        if(subject != "所有学科" && subject != file.get_subject()) return false;
        if(type != "所有类型" && type != file.get_type()) return false;
        if(priority > file.get_prior()) return false;
        return true;
    };
    vector<CourseFile> files = cfm.filter_file(filter);
    QTableWidgetItem* info_item;
    file_table->clear();
    QStringList heads;
    heads << "文件名"<< "学科" << "类型" << "上次时间" << "路径";
    file_table->setHorizontalHeaderLabels(heads);
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
//        info_item = new QTableWidgetItem(file.get_path());
//        file_table->setItem(row,4,info_item);
    }
}

void FilterWidget::click_cell_slot(int row , int colum)
{
    if(file_table->horizontalHeader()->sectionResizeMode(colum) != 3)
        file_table->horizontalHeader()->setSectionResizeMode(colum, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    else
    {
        qDebug() << colum;
        file_table->horizontalHeader()->setSectionResizeMode(colum, QHeaderView::Interactive);
        file_table->setColumnWidth(colum,120);
    }
}
