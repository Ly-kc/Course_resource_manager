#include "addfiledialog.h"
#include "ui_addfiledialog.h"

AddFileDialog::AddFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFileDialog)
{
    ui->setupUi(this);
    //setWindowIcon(QIcon(":/logo.ico"));
    setWindowFlags(Qt::Dialog);
    setWindowTitle("设置文件信息");
    //列出组件
    QVBoxLayout * VBox = new QVBoxLayout;
    QFormLayout *FormLayout = new QFormLayout;
    name_edit = new QLineEdit;
    type_box = new QComboBox;
    subject_box = new QComboBox;
    //初始化combobox
    init_combo();
    //设置slider
    priority_slider = new QSlider;
    priority_slider->setMaximum(3);
    priority_slider->setPageStep(1);
    priority_slider->setOrientation(Qt::Horizontal);
    priority_slider->setTickPosition(QSlider::TicksBelow);
    //布局输入框
    FormLayout->addRow("name:",name_edit);
    FormLayout->addRow("subject:",subject_box);
    FormLayout->addRow("type:",type_box);
    FormLayout->addRow("priority:",priority_slider);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    //布局按钮
    QHBoxLayout * HBox = new QHBoxLayout;
    submit_button = new QPushButton("submit");
    cancel_button = new QPushButton("cancel");
    HBox->addWidget(submit_button);
    HBox->addWidget(cancel_button);
    //最后组合
    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);
    //信号与槽
    QObject::connect(submit_button,&QPushButton::clicked,this,&AddFileDialog::save);
    QObject::connect(cancel_button,&QPushButton::clicked,this,&AddFileDialog::cancel); //------------待考虑

    setStyleSheet("QPushButton{\
    border:2px groove gray;\
    border-radius:10px;\
    padding:2px 4px;\
    border-style:inset;\
    color:rgb(0,0,0);\
    }\
    QPushButton:pressed{\
    background-color:rgb(200,200,200);\
    border-style:inset;\
    color:rgb(121,112,52);\
    }\
    QComboBox{\
    border:1px solid #eeeeee;\
    border-radius:4px;\
    padding:1px 2px 1px 2px ;\
    background:#ffffff;\
    font-size:14px;\
    color:#333333;\
    font-family:KaiTi;\
    }\
    QComboBox:checked{\
    border:1px solid #069aae;\
    }\
    QComboBox QAbstractItemView{\
    outline: 0px solid gray;\
    border:1px solid #eeeeee;\
    color:#333333;\
    font-size:14px;\
    font-family:KaiTi;\
    background-color:#ffffff;\
    selection-color:#333333;\
    selection-background-color:#f1f8ff;\
    }\
    QComboBox::drop-down {\
    subcontrol-origin: padding;\
    subcontrol-position: top right;\
    width: 16px;\
    }\
    ");

    name_edit->setStyleSheet("QLineEdit{\
    border:1px solid gray;\
    border-radius:4px;\
    border-bottom-right-radius:4px ;\
    border-top-left-radius:4px ;\
    font-family:KaiTi;\
    }\
    ");

    priority_slider->setStyleSheet("QSlider::groove:horizontal{\
    border:0px solid #bbb;\
    }\
    QSlider::sub-page:horizontal{\
    background:rgb(90,49,255);\
    border-radius:2px;\
    margin-top:8px;\
    margin-bottom:8px;\
    }\
    QSlider::add-page:horizontal{\
    background:rgb(255,255, 255);\
    border:0px solid #777;\
    border-radius:2px;\
    margin-top:9px;\
    margin-bottom:9px;\
    }\
    QSlider::handle:horizontal{\
    background: rgb(193,204,208);\
    width:5px;\
    border:1px solid rgb(193,204,208);\
    border-radius:2px;\
    margin-top:6px;\
    margin-bottom:6px;\
    }\
    QSlider::handle:horizontal:hover{\
    background:rgb(193,204,208);\
    width:10px;\
    border:1px solid rgb(193,204,208);\
    border-radius:5px;\
    margin-top:4px;\
    margin-bottom:4px;\
    }\
    ");
}

void AddFileDialog::init_combo()
{
    QStringList type_list;
    QStringList subject_list;
    vector<CourseFile> files = cfm.filter_file();
    type_list<<"自定义";
    subject_list<<"自定义";
    for(auto file:files)
    {
        bool flag1 = false , flag2 = false;
        for(int i = 0 ; i < type_list.size() ; i ++)
            if(type_list[i] == file.get_type())
            {
                flag1 = true;
                break;
            }
        for(int i = 0 ; i < subject_list.size() ; i ++)
            if(subject_list[i] == file.get_subject())
            {
                flag2 = true;
                break;
            }
        if(!flag1) type_list.append(file.get_type());
        if(!flag2) subject_list.append(file.get_subject());
    }
    subject_box->setEditable(true);
    type_box->setEditable(true);
    type_box->addItems(type_list);
    subject_box->addItems(subject_list);
}

void AddFileDialog::cancel()
{
    type = "cancel";
    this->close();
}
void AddFileDialog::set_file(QString name)
{
    name_edit->setPlaceholderText(name);
    file_name = name;
    this->show();
}

void AddFileDialog::save()
{
    if(name_edit->text()!="") file_name = name_edit->text();
    type = type_box->currentText();
    subject = subject_box->currentText();
    priority = priority_slider->value();
    this->close();
}

CourseFile get_course_file(QString name)
{
    AddFileDialog dia;
    dia.set_file(name);
    dia.exec();
    CourseFile cf(dia.subject.toStdString(),dia.type.toStdString(),dia.file_name.toStdString(),dia.priority);
    return cf;
}

AddFileDialog::~AddFileDialog()
{
    delete ui;
}
