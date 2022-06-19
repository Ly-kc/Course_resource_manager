#include "weblist.h"


WebList::WebList(QWidget *parent) : QWidget(parent)
{
    whole_layout = new QVBoxLayout;
    web_list = new QListWidget;
    init_list();
    whole_layout->addWidget(web_list);
    this->setLayout(whole_layout);
}

void WebList::init_list()
{
    for(int i = 0 ; i < 5 ; i ++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        QString str=QString("web %1").arg(i);
        item->setText(str);
        item->setTextAlignment(Qt::AlignCenter);
        web_list->addItem(item);
    }
}

WebList::~WebList()
{

}
