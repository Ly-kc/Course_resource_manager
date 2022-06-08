#include "filetree.h"

FileTree::FileTree(QWidget *parent):QTreeWidget(parent)
{
    this->setObjectName("TreeMenu");
    this->verticalScrollBar()->setObjectName("TreeMenuVerticl");
    this->horizontalScrollBar()->setObjectName("TreeMenuHorizontal");

    this->setColumnCount(1);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->setAutoScroll(true);
    this->header()->setVisible(false);   //隐藏横向表头

    this->setFrameStyle(QFrame::Sunken);
    this->setAnimated(true); //展开折叠动画

    // 创建右击文件夹的菜单栏
    dirMenu = new QMenu();
    dirMenu->addAction("新建文件");
    dirMenu->addAction("重命名");
    dirMenu->addSeparator();
    dirMenu->addAction("新建文件夹");
    dirMenu->addAction("删除文件夹");
    // 创建右击文件的菜单栏
    fileMenu = new QMenu();
    fileMenu->addAction("重命名");
    fileMenu->addAction("删除文件");
    fileMenu->addAction("打开所在文件夹");
    add_top(); // flush??
//    connect(dirMenu,SIGNAL(triggered(QAction*)),this,SLOT(tempActionInformation(QAction*)));
//    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(tempActionInformation(QAction*)));

    connect(this,&QTreeWidget::itemClicked,this,&FileTree::item_clicked_slot);
//    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(DoubleClickpath(QTreeWidgetItem*,int)));
//    connect(this,SIGNAL(collapseItemSignal(const QTreeWidgetItem*)),this,SLOT(collapseItem(const QTreeWidgetItem*)));
}

void FileTree::add_top()
{
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
            root = new QTreeWidgetItem();
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
            QTreeWidgetItem* type_item = new QTreeWidgetItem();
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
        QTreeWidgetItem *child = new QTreeWidgetItem(type_item);
        child->setText(0,file_name);
        child->setToolTip(0,file_path);
    }
}

void FileTree::item_clicked_slot(QTreeWidgetItem* parent_item)
{
    qDebug()<<"fashengshenmeshihou";
    if(parent_item->childCount() > 0)
    {
        if(parent_item->isExpanded()) parent_item->setExpanded(false);
        else parent_item->setExpanded(true);
    }
    else
    {
        //open file with default pro
    }

}

FileTree::~FileTree()
{

}
