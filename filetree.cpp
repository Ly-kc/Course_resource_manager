#include "filetree.h"
#define qout qDebug()

FileTree::FileTree(QWidget *parent):QTreeWidget(parent)
{

    //一通设置
    this->setColumnCount(1);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setAutoScroll(true);
    this->header()->setVisible(false);   //隐藏横向表头
    this->setFrameStyle(QFrame::Sunken);
    this->setAnimated(true); //展开折叠动画
    // 创建右击文件夹的菜单栏
    dir_menu = new QMenu();
    dir_menu->addAction("打开文件夹");
    // 创建右击文件的菜单栏
    file_menu = new QMenu();
    file_menu->addAction("删除文件");
    file_menu->addAction("打开文件");
    file_menu->addAction("打开所在文件夹");
    flush();
    this->setContextMenuPolicy(Qt::CustomContextMenu); //右键单击
    connect(this,&QTreeWidget::customContextMenuRequested,this,&FileTree::show_menu);//右键单击
    connect(dir_menu,&QMenu::triggered,this,&FileTree::tempActionInformation);
    connect(file_menu,&QMenu::triggered,this,&FileTree::tempActionInformation);
    connect(this,&QTreeWidget::itemClicked,this,&FileTree::item_clicked_slot);//左键单击
    connect(this,&QTreeWidget::itemDoubleClicked,this,&FileTree::double_clicked_slot);
}

void FileTree::flush()
{
    this->clear();
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return file.get_type() != "sticky";});
    vector<QString> subject;
    QString sub_name;
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        sub_name = i->get_subject();
        if(std::find(subject.begin(), subject.end(), sub_name) == subject.end())
        {
           // qDebug()<< sub_name;
            subject.push_back(sub_name);
            root = new QTreeWidgetItem(DIR);
            this->addTopLevelItem(root);
            root->setText(0,sub_name);
            add_typeitem(root);
        }
    }
}

void FileTree::add_typeitem(QTreeWidgetItem* sub_item)
{
    QString sub_name = sub_item->text(0);
    vector<QString> types;
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return(file.get_subject() == sub_name);});
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        QString file_type = i->get_type();
        if(std::find(types.begin(), types.end(), file_type) == types.end())
        {
           // qDebug() << file_type;
            types.push_back(file_type);
            QTreeWidgetItem* type_item = new QTreeWidgetItem(DIR);
            sub_item->addChild(type_item);
            type_item->setText(0,file_type);
            //type_item->setToolTip(0,PathContent+"/"+AllDirName[i])
            add_fileitem(type_item);
        }
    }
}

void FileTree::add_fileitem(QTreeWidgetItem *type_item)
{
    QString type_name = type_item->text(0);
    QString sub_name = type_item->parent()->text(0);
    vector<CourseFile> files = cfm.filter_file([&](CourseFile file){return(file.get_type() == type_name && file.get_subject() == sub_name);});
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        QString file_name = i->get_name();
        QString file_path = i->get_path();
        QTreeWidgetItem *child = new QTreeWidgetItem(type_item,FILE);
        child->setText(0,file_name);
        child->setToolTip(0,file_path);
    }
}

CourseFile get_cf_from_item(QTreeWidgetItem* item){
    auto vec=cfm.filter_file([&](CourseFile cf){return cf.get_path()==item->toolTip(0);});
    return vec[0];
}

void FileTree::item_clicked_slot(QTreeWidgetItem* parent_item)//--------------------------------打开文件
{
    qDebug()<< parent_item->text(0) << " clicked";
    if(parent_item->childCount() > 0)
    {
        if(parent_item->isExpanded()) parent_item->setExpanded(false);
        else parent_item->setExpanded(true);
    }
}

void FileTree::double_clicked_slot(QTreeWidgetItem *item)
{
    if(item->type() == FILE) cfm.open_file(get_cf_from_item(item));
}

void FileTree::show_menu(QPoint pos)
{
     QTreeWidgetItem* item = this->itemAt(pos);
     nowItem=item;
     //qDebug() << "1"<<nowItem->text(0);
     if(item)
     {
         if(item->type() == DIR)
         {
             dir_menu->move(this->cursor().pos());
             dir_menu->show();
         }
         else if(item->type() == FILE)
         {
             file_menu->move(this->cursor().pos());
             file_menu->show();
         }
     }
}

void FileTree::expand_to_item(QTreeWidgetItem *item) //---------------------------------------暂无用处、、
{
    QTreeWidgetItem* parent_item= item;
    if(!parent_item) return;
    qDebug() << parent_item->text(0);
    while(parent_item->parent() != NULL)
    {
        parent_item=parent_item->parent();
        qDebug() << parent_item->text(0);
    }
   // qDebug() << parent_item->text(0);
    parent_item->setExpanded(true);
    if(item->type()==FILE)
    {
        item->parent()->setExpanded(true);
    }
}

void FileTree::tempActionInformation(QAction *action)//--------------------------------一堆操作
{
    qDebug() << "2"<<nowItem->text(0);
    if(action->text() == "打开文件"){
        cfm.open_file(get_cf_from_item(nowItem));
    }
    if(action->text() == "删除文件"){
        cfm.erase_file(get_cf_from_item(nowItem));
        delete nowItem;
    }
    if(action->text() == "打开所在文件夹")
    {

    }
    if(action->text() == "打开文件夹")
    {

    }
}

FileTree::~FileTree()
{

}
