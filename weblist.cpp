#include "weblist.h"

LinkInfo::LinkInfo(QString _name,QString _link):name(_name),link(_link){}

bool operator == (const LinkInfo&x,const LinkInfo&y){
    return x.name==y.name && x.link==y.link;
}

WebList::WebList(QWidget *parent) : QWidget(parent)
{
    whole_layout = new QVBoxLayout;
    web_list = new QListWidget;
    but=new QPushButton;
    link_file=new QFile("links.txt");
    if(link_file->open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream fin(link_file);
        while(!fin.atEnd()){
            QString x,y;
            fin>>x>>y;
            info_list.append(LinkInfo(x,y));
        }
        link_file->close();
    }
    refresh();
    whole_layout->addWidget(but);
    whole_layout->addWidget(web_list);
    this->setLayout(whole_layout);
    but->setText(tr("新建链接"));
    connect(but,&QPushButton::clicked,this,&WebList::new_link);
    connect(web_list,&QListWidget::itemClicked,this,&WebList::open_link);
    connect(web_list,&QListWidget::itemDoubleClicked,this,&WebList::del_link);
}

void WebList::refresh()
{
    web_list->clear();
    for(auto info:info_list){
        auto item = new QListWidgetItem(info.name,web_list);
        item->setToolTip(info.link);
    }
}

void WebList::new_link(){
    bool ok;
    QString name=QInputDialog::getText(this,tr("new link"),tr("enter link name:"),QLineEdit::Normal,"",&ok);
    if(!ok) return;
    QString link=QInputDialog::getText(this,tr("new link"),tr("enter link url:"),QLineEdit::Normal,"",&ok);
    if(ok && !name.isEmpty()){
        info_list.append(LinkInfo(name,link));
        refresh();
    }
}

void WebList::open_link(QListWidgetItem* item){
    QDesktopServices::openUrl(QUrl(item->toolTip(), QUrl::TolerantMode));
}

void WebList::del_link(QListWidgetItem *item){
    info_list.removeAll(LinkInfo(item->text(),item->toolTip()));
    refresh();
}

WebList::~WebList()
{
    qout<<"destruct weblist";
    link_file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream fout(link_file);
    for(auto info:info_list){
        fout<<info.name<<' '<<info.link<<'\n';
    }
    link_file->close();
}
