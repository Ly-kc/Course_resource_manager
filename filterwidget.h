#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include<datamanager.h>
#include<addfiledialog.h>
#include<mainwindow.h>
#include<QTableWidget>
#include <QScrollArea>
#include<QGroupBox>
#include<datamanager.h>
#include<QScrollBar>

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
    void show_result();
    void init_combo();
    void init_result();
signals:

};

#endif // FILTERWIDGET_H
