#include "weblist.h"

LinkInfo::LinkInfo(QString _name,QString _link):name(_name),link(_link){}

bool operator == (const LinkInfo&x,const LinkInfo&y){
    return x.name==y.name && x.link==y.link;
}

WebList::WebList(QWidget *parent) : QWidget(parent)
{
    whole_layout = new QVBoxLayout;

    menu = new QMenu;
    menu->addAction("删除网址");
    web_list = new QListWidget;
    web_list->setContextMenuPolicy(Qt::CustomContextMenu);
    but=new QPushButton;
    but->setText(tr("新建链接"));

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

    //connect(but,&QPushButton::clicked,this,&WebList::new_link);
    connect(but,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->WebList::new_link();
        });
    });
    connect(web_list,&QListWidget::customContextMenuRequested,this,&WebList::show_menu);
    connect(menu,&QMenu::triggered,this,&WebList::del_link);
    connect(web_list,&QListWidget::itemClicked,this,&WebList::open_link);

    web_list->setStyleSheet("QListWidget{\
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

    but->setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(255,235,205);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    ");
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

void WebList::del_link(){
    if(curr_item) info_list.removeAll(LinkInfo(curr_item->text(),curr_item->toolTip()));
    refresh();
}

void WebList::show_menu(QPoint pos)
{
    curr_item = 0;
    QListWidgetItem* item = web_list->itemAt(pos);
    if(item)
    {
       //qDebug() << "1"<<item->text();
       curr_item = item;
    }
    menu->move(this->cursor().pos());
    menu->show();
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
