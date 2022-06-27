#include "recent.h"

Recent::Recent(QWidget *parent) : QWidget(parent)
{
    whole_layout = new QVBoxLayout;

    title = new QLabel;
    title->setText("最近打开");

    name_list = new QListWidget;
    refresh();

    whole_layout->addWidget(title);
    whole_layout->addWidget(name_list);
    this->setLayout(whole_layout);

    connect(name_list,&QListWidget::itemClicked,this,&Recent::open_file);

    title->setStyleSheet("QLabel{\
    color:rgb(255,235,205);\
    font-family:KaiTi;\
    }\
    ");

    name_list->setStyleSheet("QListWidget{\
    outline:none;\
    border:none;\
    font-family:KaiTi;\
    }\
    QListWidget::item{\
    padding-top:24px;\
    color:rgba(121,112,52,1);\
    margin-left:40px;\
    }\
    QListWidget::item:hover{\
    background-color:transparent;\
    border-bottom:1px solid rgb(121,112,52);\
    }\
    QListWidget::item:selected{\
    border-bottom:1px solid rgb(121,112,52);\
    padding:0px;\
    margin:0px;\
    color:red;\
    }\
    QListWidget::item:selected:!active{\
    border-width:0px;\
    }\
    ");
}

void Recent::refresh(){
    name_list->clear();
    cfs=cfm.filter_file([&](CourseFile file){return file.get_type() != "sticky";});
    sort(cfs.begin(),cfs.end(),[](CourseFile x,CourseFile y){
        return x.get_time()>y.get_time();
    });
    for(auto x:cfs){
        auto item=new QListWidgetItem(x.get_name(),name_list);
        item->setToolTip(x.get_time().toString("yyyy/MM/dd HH:mm:ss"));
    }
}

void Recent::open_file(QListWidgetItem* item){
    auto tmp=cfm.filter_file([&](CourseFile x){
        return x.get_name()==item->text() &&
        x.get_time().toString("yyyy/MM/dd HH:mm:ss")==item->toolTip();
    })[0];
    cfm.open_file(tmp);
    refresh();
}
