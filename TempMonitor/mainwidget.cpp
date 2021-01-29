#include "mainwidget.h"
#include<QDebug>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    chartView=new QChartView
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
    connect(dataSocket,&QTcpSocket::readyRead,[this](){
        //qDebug()<<dataSocket->readAll();
        //按照低8位和高8位数据转换成真正的温度数据
        short temp=0;
        dataSocket->read((char *)&temp,2);
        short t=temp>>8;
        float realTemp=t+(temp & 0x00ff)/100.00;
        qDebug()<<realTemp;

    });
}
