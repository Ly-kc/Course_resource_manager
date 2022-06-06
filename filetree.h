#ifndef FILETREE_H
#define FILETREE_H
#include<mainwindow.h>
#include<QTreeWidget>
#include<QMenu>
#include<QScrollBar>
#include<QHeaderView>

class FileTree:public QTreeWidget
{
    Q_OBJECT
public:
    FileTree(QWidget *parent = 0);
    ~FileTree();
    QTreeWidgetItem *root; //树的根
    QMenu *dirMenu;  //文件夹菜单栏
    QMenu *fileMenu;  //文件菜单栏
    QTreeWidgetItem *nowItem; //当前光标所在Item
    int nowCol; //当前所在列
    void init_add();

};

#endif // FILETREE_H
