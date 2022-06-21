#include "statchart.h"
using namespace QtCharts;

StatChart::StatChart(QWidget *parent) : QWidget(parent)
{

    whole_layout = new QVBoxLayout;
    head_layout = new QHBoxLayout;
    body_layout = new QStackedLayout;

    switch_combo = new QComboBox;
    QStringList chart_names;
    chart_names << "学科频率统计" << "软件使用时长";
    switch_combo->addItems(chart_names);

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
    mAxY->setRange(0, 10);
    // Y轴分等份
    mAxY->setTickCount(11);
    mAxX->setRange(0,10);
    mAxX->setTickCount(11);
    // 将系列添加到图表
    line_chart->addSeries(mLineSeries);
    line_chart->setTheme(QtCharts::QChart::ChartThemeBrownSand);
    mAxX->setTitleText(QString(tr("ImageNumber")));
    mAxY->setTitleText(QString(tr("ReadRate(%)")));
    line_chart->addAxis(mAxY, Qt::AlignLeft);
    line_chart->addAxis(mAxX, Qt::AlignBottom);
    mLineSeries->attachAxis(mAxY);
    mLineSeries->attachAxis(mAxX);
    //背景
    line_chart->setTheme(QChart::ChartThemeBlueCerulean);
    //chart->setBackgroundVisible(false);

    //设置外边界全部为0
    line_chart->setContentsMargins(0, 0, 0, 0);
    //设置内边界全部为0
    line_chart->setMargins(QMargins(0, 0, 0, 0));
    //设置背景区域无圆角
    line_chart->setBackgroundRoundness(0);
    //突出曲线上的点
    mLineSeries->setPointsVisible(true);
    //图例
    QLegend *mlegend = line_chart->legend();
    mLineSeries->setName("testname");


    mLineSeries->setColor(QColor(255,0,0));
    //在底部显示
    mlegend->setAlignment(Qt::AlignBottom);
    mlegend->show();
    // 将图表绑定到视图 wiget 为 QChartView
    line_chartview->setRenderHint(QPainter::Antialiasing); //抗锯齿
    line_chartview->setChart(line_chart);
    for(int i = 0 ;i < 10;i++){
        mLineSeries->append(i+1, i);
    }
}

void StatChart::paint_pie()
{
    //创建饼状图的数据系列对象，并添加相应的数据
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
//    series->slices().at(0)->setColor(QColor(13,128,217));   //设置颜色
//    series->slices().at(0)->setLabelColor(QColor(13,128,217));

//    series->slices().at(1)->setColor(QColor(255,0,0));
//    series->slices().at(1)->setLabelColor(QColor(255,0,0));

    pie_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    pie_chart->setDropShadowEnabled(true);//背景阴影
    pie_chart->addSeries(series);//添加系列到QChart上
    pie_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    pie_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    pie_chart->setTitle("学科访问频率");

    pie_chartview->setRenderHint(QPainter::Antialiasing);
}

StatChart::~StatChart()
{

}
