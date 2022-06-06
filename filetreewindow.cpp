#include "filetreewindow.h"
#include "ui_filetreewindow.h"
#include<QTreeWidget>

FileTreeWindow::FileTreeWindow(QString file_name,QString dir_path,QDataStream& writeInfoStr,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileTreeWindow)
{
    QTreeWidget *treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(2);
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 3; ++i){
        QStringList ql;
        ql.append(QString("item: %1").arg(i));
        ql.append(QString("date %2").arg(i*60));
        items.append(new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), ql));
    }
    treeWidget->insertTopLevelItems(0, items);
    ui->setupUi(this);
}

FileTreeWindow::~FileTreeWindow()
{
    delete ui;
}
