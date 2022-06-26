#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include<algorithm>
#include"QtHeaderFiles.h"
#include<filterwidget.h>
#include<datamanager.h>

class NotesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotesWidget(QWidget *parent = nullptr);
    QPushButton* addnotes_button;
    QMenu* menu;
    QListWidget* notes_list;
    QListWidgetItem* curr_item;
    std::vector<CourseFile> notes;
    void action_reflect(QAction* action);
    void show_menu(QPoint pos);
    void add_note();
    void get_notes();
    ~NotesWidget();
    void init_list();
signals:

};

#endif // NOTESWIDGET_H
