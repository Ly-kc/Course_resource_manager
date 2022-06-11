#include "noteswidget.h"

NotesWidget::NotesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* whole_layout = new QVBoxLayout;

    addnotes_button = new QPushButton;
    addnotes_button->setText("+添加便签");

    notes_list = new QListWidget;
    //QLabel note_text("发生甚么事了");
    QListWidgetItem* note_item = new QListWidgetItem;
    note_item->setText("马老师，发生甚么事了");
    notes_list->setWordWrap(true);
    note_item->setTextAlignment(Qt::AlignCenter);
    notes_list->addItem(note_item);

    whole_layout->addWidget(addnotes_button);
    whole_layout->addWidget(notes_list);
    whole_layout->addStretch(1);
    this->setLayout(whole_layout);
}
