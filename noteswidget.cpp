#include "noteswidget.h"

NotesWidget::NotesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* whole_layout = new QVBoxLayout;

    addnotes_button = new QPushButton;
    addnotes_button->setText("+添加便签");

    menu = new QMenu;
    menu->addAction("删除便签");
    menu->addAction("置顶"); //仅在以prior排序时生效
    menu->addAction("按优先级排序");

    notes_list = new QListWidget;
    init_list();

    whole_layout->addWidget(addnotes_button);
    whole_layout->addWidget(notes_list);
    whole_layout->addStretch(1);
    this->setLayout(whole_layout);
}

void NotesWidget::init_list()
{
    //QLabel note_text("发生甚么事了");
    QListWidgetItem* note_item = new QListWidgetItem;
    note_item->setText("· 马老师，发生甚么事了");
    notes_list->setWordWrap(true);
    note_item->setTextAlignment(Qt::AlignCenter);
    notes_list->addItem(note_item);
    QTreeWidget* note = new QTreeWidget;
    note->setColumnCount(1);
    note->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    note->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    note->setAutoScroll(true);
    note->header()->setVisible(false);   //隐藏横向表头
    note->setFrameStyle(QFrame::Sunken);
    note->setAnimated(true); //展开折叠动画
    QTreeWidgetItem* title = new QTreeWidgetItem;
    title->setText(0,"点开啥都没");
    QTreeWidgetItem* content = new QTreeWidgetItem;
    content->setText(0,"点开我干啥");
    title->addChild(content);
    note->addTopLevelItem(title);
    QListWidgetItem* new_note_item = new QListWidgetItem;
    notes_list->addItem(new_note_item);
    QWidget *w = new QWidget;
    QHBoxLayout *layout=new QHBoxLayout;
    note->setIndentation(0);
    layout->addWidget(note);
    w->setLayout(layout);
//    w->show();
    new_note_item->setSizeHint(QSize(100,60));
    notes_list->setItemWidget(new_note_item,w);
}

NotesWidget::~NotesWidget()
{

}
