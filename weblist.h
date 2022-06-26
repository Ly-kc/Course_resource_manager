#ifndef WEBLIST_H
#define WEBLIST_H

#include<QtHeaderFiles.h>
#include<mainwindow.h>

#ifndef qout
#define qout qDebug()
#endif

class WebList;

class LinkInfo{
    QString name,link;
public:
    LinkInfo(QString _name="",QString _link="");
    friend class WebList;
    friend bool operator == (const LinkInfo&,const LinkInfo&);
};

class WebList : public QWidget
{
    Q_OBJECT
public:
    explicit WebList(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QListWidget* web_list;
    QList<LinkInfo> info_list;
    QPushButton* but;
    QFile* link_file;
    QMenu* menu;
    QListWidgetItem* curr_item;
    void refresh();
    void new_link();
    void action_reflect(QAction* action);
    void show_menu(QPoint pos);
    void del_link();
    void open_link(QListWidgetItem*);
    ~WebList();
signals:

};

#endif // WEBLIST_H
