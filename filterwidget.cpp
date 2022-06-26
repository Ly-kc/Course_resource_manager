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
    file_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    file_table->setContextMenuPolicy(Qt::CustomContextMenu); //右键单击
    //完成menu
    menu = new QMenu;
    menu->addAction("修改文件信息");
    menu->addAction("新增筛选窗口");
    menu->addAction("删除筛选窗口");
    curr_item = 0;
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
    connect(file_table->horizontalHeader(),&QHeaderView::sectionPressed,this,&FilterWidget::click_header_slot);
    connect(file_table,&QTableWidget::customContextMenuRequested,this,&FilterWidget::show_menu);//右键单击
    connect(menu,&QMenu::triggered,this,&FilterWidget::action_reflect);
    connect(file_table,&QTableWidget::cellDoubleClicked,this,&FilterWidget::open_file);
}

void FilterWidget::init_combo()
{
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return file.get_type() != "sticky";});
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
    times << "所有时间" << "今日" << "两天内" << "三天内";
    prior_filter->addItems(priority);
    time_filter->addItems(times);
}

void FilterWidget::init_result()
{
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return file.get_type() != "sticky";});
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

CourseFile FilterWidget::row_to_cf(int row){
    auto sub=file_table->item(row,1)->text();
    auto typ=file_table->item(row,2)->text();
    auto nam=file_table->item(row,0)->text();
    return CourseFile(sub,typ,nam);
}

void FilterWidget::show_result()
{
    QString name = name_edit->text();
    QString subject = sub_filter->currentText();
    QString type = type_filter->currentText();
    int priority = prior_filter->currentIndex();
    int days = time_filter->currentIndex();
    if(days == 0) days = (1<<30);
    auto filter = [&](CourseFile file){
        std::regex name_reg(name.toStdString());
        if(file.get_type() == "sticky") return false;
        bool ret = std::regex_search(file.get_name().toStdString(), name_reg);
        if(name != "" && !ret) return false;
        if(subject != "所有学科" && subject != file.get_subject()) return false;
        if(type != "所有类型" && type != file.get_type()) return false;
        if(priority > file.get_prior()) return false;
        if(file.get_time().addDays(days).date() <= QDateTime::currentDateTime().date()) return false;
        return true;
    };
    vector<CourseFile> files = cfm.filter_file(filter);
    QTableWidgetItem* info_item;
    file_table->clear();
    QStringList heads;
    heads << "文件名"<< "学科" << "类型" << "上次时间";       //<< "路径";
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

void FilterWidget::click_header_slot(int colum)
{
    if(file_table->horizontalHeader()->sectionResizeMode(colum) != 3)
        file_table->horizontalHeader()->setSectionResizeMode(colum, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    else
    {
        //qDebug() << "cloum " <<colum;
        file_table->horizontalHeader()->setSectionResizeMode(colum, QHeaderView::Interactive);
        file_table->setColumnWidth(colum,120);
    }
}

void FilterWidget::open_file(int row , int colum)
{
    QTableWidgetItem* info_item = file_table->item(row,0);
    if(!info_item) return;
    QString name = info_item->text();
    info_item = file_table->item(row,1);
    QString subject = info_item->text();
    info_item = file_table->item(row,2);
    QString type = info_item->text();
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){
         if(file.get_name() != name || file.get_subject() != subject || file.get_type() != type) return false;
         return true;
    });
    if(files.size() > 0) cfm.open_file(files[0]);
}

void FilterWidget::show_menu(QPoint pos)
{
     QTableWidgetItem* item = file_table->itemAt(pos);
     if(item)
     {
        //qDebug() << "1"<<item->text();
        curr_item = item;
     }
     menu->move(this->cursor().pos());
     menu->show();
}

void FilterWidget::action_reflect(QAction *action)
{
    auto item=curr_item;
    if(item != 0x0 && action->text() == "修改文件信息")
    {
        int row=item->row(),col=item->column();
        auto cf=row_to_cf(row);
        bool ok;
        if(col>2) return;
        QString lab = "输入新"+file_table->horizontalHeaderItem(col)->text();
        QString text = QInputDialog::getText(this, tr("Fuck QT!"),
                                                 lab, QLineEdit::Normal,
                                                 item->text(), &ok);
        if(ok && !text.isEmpty()){
            qout<<text;
            item->setText(text);
            auto ncf=row_to_cf(row);
            qout<<cf;
            qout<<ncf;
            cfm.transform_file([=](CourseFile){return ncf;},[=](CourseFile cur){return cur==cf;});
        }
        emit mod_table_signal();
    }
    if(action->text() == "新增筛选窗口")  emit add_table_signal();
    if(action->text() == "删除筛选窗口") emit del_table_signal();
    curr_item = 0;
}

FilterWidget::~FilterWidget()
{

}
