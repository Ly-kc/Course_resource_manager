#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include"QtHeaderFiles.h"
#include<datamanager.h>
#include<addfiledialog.h>


class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QHBoxLayout* head_layout;
    QHBoxLayout* table_layout;
    QHBoxLayout* combo_layout;
    QPushButton* filter_button;
    QLineEdit* name_edit;
    QComboBox* sub_filter;
    QComboBox* time_filter;
    QComboBox* type_filter;
    QComboBox* prior_filter;
//    QScrollArea* filter_area;
    QTableWidget* file_table;
    QStringList subjects;
    QStringList types;
    QMenu* menu;
    QTableWidgetItem* curr_item;
    void show_result(); //显示筛选结果
    void init_combo();
    void init_result(); //显示所有文件
    void click_header_slot(int colum);
    void open_file(int row , int colum);
    void action_reflect(QAction* action);
    void show_menu(QPoint pos);
    ~FilterWidget();
signals:
    void add_table_signal();
    void del_table_signal();
};

#endif // FILTERWIDGET_H
