#ifndef INTROWIDGET_H
#define INTROWIDGET_H

#include <QWidget>
#include <QtHeaderFiles.h>


class IntroWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntroWidget(QWidget *parent = nullptr);
    QWizard* intro_widget;
    QWizardPage* page1;
    QWizardPage* page2;
    QWizardPage* page3;

    void show_intro();
signals:

};

#endif // INTROWIDGET_H
