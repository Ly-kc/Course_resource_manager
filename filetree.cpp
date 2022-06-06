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
    init_add();
//    connect(dirMenu,SIGNAL(triggered(QAction*)),this,SLOT(tempActionInformation(QAction*)));
//    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(tempActionInformation(QAction*)));

//    connect(this,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(itemPressedSlot(QTreeWidgetItem*,int)));
//    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(DoubleClickpath(QTreeWidgetItem*,int)));
//    connect(this,SIGNAL(collapseItemSignal(const QTreeWidgetItem*)),this,SLOT(collapseItem(const QTreeWidgetItem*)));
}

void FileTree::init_add()
{

}

FileTree::~FileTree()
{

}
