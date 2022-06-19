#ifndef RECENTFILELIST_H
#define RECENTFILELIST_H

#include <QWidget>
#include<mainwindow.h>

class RecentFileList : public QWidget
{
    Q_OBJECT
public:
    explicit RecentFileList(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QListWidget* web_list;
    void init_list();
signals:

};

#endif // RECENTFILELIST_H
