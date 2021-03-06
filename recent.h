#ifndef RECENT_H
#define RECENT_H

#include<QtHeaderFiles.h>
#include"datamanager.h"

#ifndef qout
#define qout qDebug()
#endif

class Recent : public QWidget
{
    Q_OBJECT
public:
    explicit Recent(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QLabel* title;
    QListWidget* name_list;
    std::vector<CourseFile> cfs;
    void refresh();
    void open_file(QListWidgetItem*);
signals:   

};

#endif // RECENT_H
