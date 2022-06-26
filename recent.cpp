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
