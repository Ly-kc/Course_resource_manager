#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

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
    ~NotesWidget();
    void init_list();
signals:

};

#endif // NOTESWIDGET_H
