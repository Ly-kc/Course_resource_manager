#ifndef WEBLIST_H
#define WEBLIST_H

#include <QWidget>
#include<mainwindow.h>

class WebList : public QWidget
{
    Q_OBJECT
public:
    explicit WebList(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QListWidget* web_list;
    void init_list();
    ~WebList();
signals:

};

#endif // WEBLIST_H
