#include "mainwidget.h"
#include<QDebug>
#include<QtCharts/QValueAxis>

void MainWidget::createChart()
{
    //配置基础图表数据
    mainChart=new QChart();
    dotSeries=new QScatterSeries;
    //XY坐标系
    QValueAxis *axisX=new QValueAxis;
    QValueAxis *axisY=new QValueAxis;
    //数值范围
    axisX->setRange(0,60);
    //数据形式
    axisX->setLabelFormat("%.2f");
    //是否显示表格分割虚线
    axisX->setGridLineVisible(true);
    //分割的格子数
    axisX->setTickCount(7);
    //最小分割
    axisX->setMinorTickCount(1);
    //坐标代表的含义标题
    axisX->setTitleText("时间");

    axisY->setRange(34,43);
    axisY->setLabelFormat("%.2f");
/*
    //设置颜色
    axisY->setGridLineColor(Qt::red);

    //是否显示表格分割虚线
    axisX->setGridLineVisible(true);
    */
    //分割的格子数
    axisY->setTickCount(10);
    //最小分割
    axisY->setMinorTickCount(1);
    axisY->setTitleText("体温");

    mainChart->addAxis(axisX,Qt::AlignBottom);
    mainChart->addAxis(axisY,Qt::AlignLeft);
    mainChart->addSeries(dotSeries);
    //隐藏图例
    mainChart->legend()->hide();
//需要将坐标系和数值范围绑定在一起，否则显示数据不正确
    dotSeries->attachAxis(axisX);
    dotSeries->attachAxis(axisY);
    /*
    for (int i=0;i<43;i++) {
        dotSeries->append(i,i);
    }
*/

}
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),chartview(new QChartView(this)),currentTempLabel(new QLabel(this)),
      currentLcdNumber(new QLCDNumber(this))
{
    this->setGeometry(200,200,800,600);
    this->setMinimumSize(400,300);
    createChart();

    //对于绝大部分界面元素，创建对象时，可以添加父元素的指针，代表加到父界面
    //chartview=new QChartView(this);
    chartview->setGeometry(200,0,600,400);
    chartview->setChart(mainChart);

    currentTempLabel->setGeometry(0,0,200,40);
    //currentTempLabel->font(QFont(18));
    currentTempLabel->setText("体温数据");
    QFont f;
    f.setBold(true);
    f.setPixelSize(18);
    currentTempLabel->setFont(f);
    currentTempLabel->setStyleSheet("color:#336699");

    currentLcdNumber->setGeometry(0,50,180,40);
    //currentLcdNumber->display(12);

    //qDebug()<<QTime::currentTime().minute();

    if(startServer())
    {
        qDebug()<<"等待连接";
        /*
        if(server->waitForNewConnection())
        {
            qDebug()<<"有新连接进入";
        }
        */
        connect(server,SIGNAL(newConnection()),this,SLOT(newConnectionAccept()));
    }
}

MainWidget::~MainWidget()
{
}
bool MainWidget::startServer()
{
    server=new QTcpServer();
    return server->listen(QHostAddress("127.0.0.1"),8888);
}

void MainWidget::newConnectionAccept()
{
    qDebug()<<"有新连接进入";
    //server->write("hello ");
    //获取当前传输套接字，可以进行数据发送和接收
    dataSocket=server->nextPendingConnection();
    dataSocket->write("hello");
    //qDebug()<<dataSocket->readAll();
    //客户端是否有新的数据发送
    //有-触发readyread信号，可对数据进行处理

    qreal passMinute=QTime::currentTime().minute();
    connect(dataSocket,&QTcpSocket::readyRead,[=]()mutable{
        //qDebug()<<dataSocket->readAll();
        //按照低8位和高8位数据转换成真正的温度数据
        short temp=0;
        dataSocket->read((char *)&temp,2);
        short t=temp>>8;
        float realTemp=t+(temp & 0x00ff)/100.00;
        qDebug()<<realTemp;
        if(passMinute!=QTime::currentTime().minute())
        {
            dotSeries->clear();
            passMinute=QTime::currentTime().minute();
        }
        dotSeries->append(QTime::currentTime().second(),realTemp);
        QString tt("当前温度为：");
        tt += QString("%1").arg(realTemp);
        QString tt1("");
        tt1 =tt+ QString("%1").arg("°C" );
        currentTempLabel->setText(tt1);
        //dotSeries->clear();
        currentLcdNumber->display(tt);

    });
}
