#include "noteswidget.h"

NotesWidget::NotesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* whole_layout = new QVBoxLayout;

    addnotes_button = new QPushButton;
    addnotes_button->setText("+添加便签");

    menu = new QMenu;
    menu->addAction("删除便签");
    menu->addAction("置顶");

    notes_list = new QListWidget;
    notes_list->setContextMenuPolicy(Qt::CustomContextMenu); //右键单击
    init_list();

    whole_layout->addWidget(addnotes_button);
    whole_layout->addWidget(notes_list);
    whole_layout->addStretch(1);
    this->setLayout(whole_layout);

    connect(addnotes_button,&QPushButton::clicked,this,&NotesWidget::add_note);
    connect(notes_list,&QListWidget::customContextMenuRequested,this,&NotesWidget::show_menu);//右键单击
    connect(menu,&QMenu::triggered,this,&NotesWidget::action_reflect);
}

void NotesWidget::get_notes()
{
    notes.clear();
    notes = cfm.filter_file([&](CourseFile file){return file.get_type() == "sticky";});
    auto cmp = [&](const CourseFile& a , const CourseFile& b){
        return a.get_prior() <b.get_prior();};
    std::sort(notes.begin() , notes.end() , cmp);
    for(int i = 0 ; i < notes.size() ; i ++)
    {
        auto filt = [&](CourseFile file){
            return file.get_type() == "sticky" && file.get_name() == notes[i].get_name();};
        auto func = [=](CourseFile file){
            file.set_prior(i);
            return file;};
        cfm.transform_file(func,filt);
    }
}

void NotesWidget::init_list()
{
    get_notes();
    notes_list->clear();
    for(auto note:notes)
    {
        QListWidgetItem* note_item = new QListWidgetItem;
        note_item->setText("✍ " + note.get_name());
        notes_list->setWordWrap(true);
        note_item->setTextAlignment(Qt::AlignCenter);
        notes_list->addItem(note_item);
    }
}

void NotesWidget::show_menu(QPoint pos)
{
     curr_item = 0;
     QListWidgetItem* item = notes_list->itemAt(pos);
     if(item)
     {
        curr_item = item;
     }
     menu->move(this->cursor().pos());
     menu->show();
}

void NotesWidget::add_note()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("新建便签"),"输入便签内容", QLineEdit::Normal,"程设大作业ddl...", &ok);
    if(ok && !name.isEmpty())
    {
        string type("sticky");
        int priority = notes.size();
        CourseFile cf("whatever",type,name.toStdString(),priority);
        cfm.new_file(cf);
        init_list();
        qDebug() << (notes.end()-1)->get_name();
    }
}

void NotesWidget::action_reflect(QAction* action)
{
    if(!curr_item) return;
    QString name = curr_item->text().split(' ')[1];
    qDebug() <<name;
    CourseFile note = cfm.filter_file([&](CourseFile file){
            return file.get_name() == name && file.get_type() == "sticky";})[0];
    qDebug() <<"OK?";
    if(action->text() == "删除便签")
    {
        cfm.erase_file(note);
        init_list();
    }
    else if(action->text() == "置顶")
    {
        auto filt = [&](CourseFile file){
            return file.get_type() == "sticky" && file.get_name() == note.get_name();};
        auto func = [=](CourseFile file){
            file.set_prior(-1);
            return file;};
        cfm.transform_file(func,filt);
        init_list();
    }
}

NotesWidget::~NotesWidget()
{

}
