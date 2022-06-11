#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include <QWidget>
#include<QListWidget>
#include<QLabel>
#include<filterwidget.h>
#include<datamanager.h>

class NotesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotesWidget(QWidget *parent = nullptr);
    QPushButton* addnotes_button;
    QListWidget* notes_list;
signals:

};

#endif // NOTESWIDGET_H
