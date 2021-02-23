/*
 *TCP客户端
 *发送数据
*/
#include<iostream>
#include<time.h>
#include<unistd.h>
#include<bitset>
#include<QTcpSocket>
#include<QHostAddress>
#include<QDebug>
#include<QThread>

using namespace std;

short gTemp;
//16位数据 高8位整数，低8位小数
short makeTemp()
{
    srand(clock());
    short temp=0;
    char high=0;
    char low=0;
    while (1) {
        usleep(100*100);
        high=34+rand()%9;
        low=34+rand()%100;

        cout<<(int)high<<endl;
        cout<<(int)low<<endl;

    //将产生的数赋值到temp 位运算
    temp=high;
    temp=temp<<8;
    //16进制和二进制输出
    cout<<"高8位16进制"<<hex<<temp<<endl;//16位进制输出
    cout<<"高8位2进制"<<bitset<16>(temp)<<endl;

    temp+=low;
    cout<<"低8位16进制"<<hex<<temp<<endl;//16位进制输出
    cout<<"低8位2进制"<<bitset<16>(temp)<<endl;


        //usleep(100*100);
        gTemp=temp;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    //开启多线程
    QThread::create([ ](){
        makeTemp();
    })->start();
    QTcpSocket *client=new QTcpSocket;
    QHostAddress address("127.0.0.1");
    client->connectToHost(address,8888);
    if(client->waitForConnected())
    {
        //对方地址和端口
        qDebug()<<"对方地址"<<client->peerAddress();
        qDebug()<<client->peerPort();
        //自己地址和端口
        qDebug()<<"自己地址"<<client->localAddress();
        qDebug()<<client->localPort();
        //获取数据
        //数据循环发送
        while (1) {
            //usleep(100*1000);
            sleep(rand()%10);
            //write用法 char *地址 数据的长度（字节）
            cout<<gTemp<<endl;
            qDebug()<<client->write((char *)&gTemp,2);
            client->flush();
        }
    }


    //makeTemp();


    return 0;
}
