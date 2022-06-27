#include "statchart.h"
using namespace QtCharts;

StatChart::StatChart(QWidget *parent) : QWidget(parent)
{

    whole_layout = new QVBoxLayout;
    head_layout = new QHBoxLayout;
    body_layout = new QStackedLayout;

    switch_combo = new QComboBox;
    QStringList chart_names;
    chart_names << "学科频率统计" << "每日打开文件频率";
    switch_combo->addItems(chart_names);
    switch_combo->setStyleSheet("QComboBox{\
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
        border-left: 0px solid darkgray;\
        border-top-right-radius: 4px;\
        border-bottom-right-radius: 4px;\
        }\
    ");

    paint_line();
    paint_pie();

    body_layout->addWidget(pie_chartview);
    body_layout->addWidget(line_chartview);
    head_layout->addWidget(switch_combo);
    head_layout->addStretch(4);
    whole_layout->addLayout(head_layout);
    whole_layout->addLayout(body_layout,1);

    this->setLayout(whole_layout);
    connect(switch_combo,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),body_layout,&QStackedLayout::setCurrentIndex);
}

void StatChart::paint_line()
{
    line_chart = new QChart;
    line_chartview = new QChartView;
    QValueAxis* mAxY = new QValueAxis;
    QValueAxis* mAxX = new QValueAxis;
    QLineSeries* mLineSeries = new QLineSeries();
    //y轴范围
    mAxY->setRange(0, 20);
    // Y轴分等份
    mAxY->setTickCount(11);
    mAxX->setRange(0,6);
    mAxX->setTickCount(7);
    // 将系列添加到图表
    line_chart->addSeries(mLineSeries);
    mAxX->setTitleText("这七日");
    mAxY->setTitleText("打开文件数");
    line_chart->addAxis(mAxY, Qt::AlignLeft);
    line_chart->addAxis(mAxX, Qt::AlignBottom);
    mLineSeries->attachAxis(mAxY);
    mLineSeries->attachAxis(mAxX);
    //背景
    line_chart->setTheme(QChart::ChartThemeBlueCerulean);
    //设置外边界全部为0
    line_chart->setContentsMargins(0, 0, 0, 0);
    //设置内边界全部为0
    line_chart->setMargins(QMargins(0, 0, 0, 0));
    //设置背景区域无圆角
    line_chart->setBackgroundRoundness(0);
    //突出曲线上的点
    mLineSeries->setPointsVisible(true);
    //图例
   // QLegend *mlegend = line_chart->legend();
    mLineSeries->setName("最近七日打开文件数");
    mLineSeries->setColor(QColor(255,0,0));
    //在底部显示
   // mlegend->setAlignment(Qt::AlignBottom);
   // mlegend->show();
    // 将图表绑定到视图 wiget 为 QChartView
    line_chartview->setRenderHint(QPainter::Antialiasing); //抗锯齿
    line_chartview->setChart(line_chart);
    for(int i = 6 ; i >= 0 ; i--){
        int num = cfm.filter_file([&](CourseFile file){
                return file.get_time().addDays(i).date() == QDateTime::currentDateTime().date() && file.get_freq() > 0;}).size();
        mLineSeries->append(6-i, num);
    }
}

void StatChart::paint_pie()
{
    pie_chart = new QChart;
    pie_chartview = new QChartView(pie_chart);
    QPieSeries *series = new QPieSeries();

    vector<CourseFile> files = cfm.filter_file();
    vector<QString> subject;
    QString sub_name;
    for(auto i = files.begin() ; i != files.end() ; i ++)
    {
        sub_name = i->get_subject();
        if(std::find(subject.begin(), subject.end(), sub_name) == subject.end())
        {
            int freq = 0;
            subject.push_back(sub_name);
            vector<CourseFile> sub_files = cfm.filter_file([&](CourseFile f){return f.get_subject() == sub_name;});
            for(auto j:sub_files) freq += j.get_freq();
            if(freq != 0) series->append(sub_name,freq);
        }
    }

    series->setLabelsVisible(true);
    series->setUseOpenGL(true);
    pie_chart->setTheme(QChart::ChartThemeBlueNcs);
    pie_chart->setDropShadowEnabled(true);//背景阴影
    pie_chart->addSeries(series);//添加系列到QChart上
    pie_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    pie_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    pie_chart->setTitle("学科访问频率");

    pie_chartview->setRenderHint(QPainter::Antialiasing);
}

void StatChart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

StatChart::~StatChart()
{

}
