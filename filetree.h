#ifndef FILETREE_H
#define FILETREE_H

#include"QtHeaderFiles.h"
#include<datamanager.h>

class FileTree:public QTreeWidget
{
    Q_OBJECT
public:
    FileTree(QWidget *parent = 0);
    ~FileTree();
    QTreeWidgetItem *root; //树的根
    QMenu *dir_menu;  //文件夹菜单栏
    QMenu *file_menu;  //文件菜单栏
    QTreeWidgetItem *nowItem; //当前光标所在Item
    QPoint curr_pos;
    int DIR = 0 , FILE = 1;  //结点的type
    void flush(); //刷新显示(包含以下两个函数)
    void add_typeitem(QTreeWidgetItem* sub_item);
    void add_fileitem(QTreeWidgetItem* type_item);
    void item_clicked_slot(QTreeWidgetItem* parent_item); //左键展开
    void show_menu(QPoint pos);  //右键菜单
    void tempActionInformation(QAction* action); //菜单动作响应
    void expand_to_item(QTreeWidgetItem* item);
};

#endif // FILETREE_H
