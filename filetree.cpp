#include "filetree.h"

FileTree::FileTree(QWidget *parent):QTreeWidget(parent)
{
//    this->setObjectName("TreeMenu");
//    this->verticalScrollBar()->setObjectName("TreeMenuVerticl");
//    this->horizontalScrollBar()->setObjectName("TreeMenuHorizontal");
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
    dir_menu->addAction("新建文件");
    dir_menu->addAction("重命名");
    dir_menu->addSeparator();
    dir_menu->addAction("新建文件夹");
    dir_menu->addAction("删除文件夹");
    // 创建右击文件的菜单栏
    file_menu = new QMenu();
    file_menu->addAction("修改信息");
    file_menu->addAction("删除文件");
    file_menu->addAction("打开所在文件夹");
    flush();
    this->setContextMenuPolicy(Qt::CustomContextMenu); //右键单击
    connect(this,&QTreeWidget::customContextMenuRequested,this,&FileTree::show_menu);//右键单击
    connect(dir_menu,&QMenu::triggered,this,&FileTree::tempActionInformation);
    connect(file_menu,&QMenu::triggered,this,&FileTree::tempActionInformation);
    connect(this,&QTreeWidget::itemClicked,this,&FileTree::item_clicked_slot);//左键单击
//    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(DoubleClickpath(QTreeWidgetItem*,int)));
}

void FileTree::flush()
{
    this->clear();
    vector<CourseFile> files = cfm.filter_file([](CourseFile file){return true;});
    vector<QString> subject;
    QString sub_name;
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        sub_name = i->get_subject();
        if(std::find(subject.begin(), subject.end(), sub_name) == subject.end())
        {
            qDebug()<< sub_name;
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
            qDebug() << file_type;
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

void FileTree::item_clicked_slot(QTreeWidgetItem* parent_item)//--------------------------------打开文件
{
    qDebug()<<"fashengshenmeshihou";
    if(parent_item->childCount() > 0)
    {
        if(parent_item->isExpanded()) parent_item->setExpanded(false);
        else parent_item->setExpanded(true);
        //QTreeWidgetItem* item = parent_item->child(0);
        //this->scrollToItem(item, EnsureVisible);
    }
    else
    {
        //open file with default pro
    }

}

void FileTree::show_menu(QPoint pos)
{
     curr_pos = pos;
     QTreeWidgetItem* item = this->itemAt(pos);
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

void FileTree::tempActionInformation(QAction *action)//--------------------------------一堆操作
{
    QTreeWidgetItem* item = this->itemAt(curr_pos);
    qDebug() << item->text(0);
    qDebug() << item->parent()->text(0);
    if(action->text() == "删除文件")
    {
    qDebug() << "hh";
    }
    if(1)
    {

    }
}

FileTree::~FileTree()
{

}
