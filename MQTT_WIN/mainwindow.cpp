#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "mqtt/qmqtt.h"
#include <string>
int flag = 0;  //判断是否连接服务器
void MainWindow::onMQTT_Connectted(){
    flag=1;

    qDebug()<<"connect success"<<endl;
    QString topicSub = "/public/test";  //先给话题确定参数，赋值
    quint8 qosSub = 0;
    client->subscribe(topicSub,qosSub);

    connect(client,SIGNAL(subscribed(const QString &)),this,SLOT(onMQTT_Subscribed(QString)));
   // qDebug()<<"111"<<endl;
    connect(client,SIGNAL(received(const QMQTT::Message &)),this,SLOT(onMQTT_Received(QMQTT::Message)));

}
//成功订阅
void MainWindow::onMQTT_Subscribed(const QString &topic){
    //原程序 ui->plainTextEdit->appendPlainText(message.topic());
   //原程序plainTextEdit改为对应的文本框的名字
   //appendPlainText()函数改为append函数，两函数功能一样，可能由于QT版本号不同，导致函数名称不同。
    ui->textEdit->append(topic);
    qDebug()<<"Subscribe success !!"<<endl;
    flag=1;
}

//接收到消息
void MainWindow::onMQTT_Received(const QMQTT::Message &message){
    ui->textEdit_2->append(message.topic());
    ui->textEdit_3->append(message.payload());
    flag=1;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  ////////////////
    this->setMaximumSize(300,355);
    this->setMinimumSize(300,255);

    // 如果没有连接服务器，显示提示信息
    if(!flag){

         ui->textEdit->append("当前未连接");
         ui->textEdit_2->append("当前未连接");
         ui->textEdit_3->append("当前未连接");

    }


    client = new QMQTT::Client(QHostAddress("127.0.0.1"),1883,0);  //new client
//    client->setClientId("MQTT_Qt");
//    client->setUsername("yks");
//    client->setPassword("123435");
    client->setCleanSession(true);
    client->connectToHost();
    connect(client,SIGNAL(connected()),this,SLOT(onMQTT_Connectted()));

   // qDebug()<<"Received = "<< received(const QMQTT::Message &) <<endl;


    //ui->textEdit_3->append(topicSub);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{   if(flag)
    {
    data += 1;
    QString Data = QString::number(data);
    QString topicPub = "/public/test";
    QString messagePub ="MQTT "+Data;
    QMQTT::Message msg(0,topicPub.toLatin1(),messagePub.toLatin1());
    client->publish(msg);
    qDebug()<<"publish success"<<endl;
    }
}
