#include "widget.h"
#include <windows.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setGeometry(500,200,300,380);

    inputLabel = new QLabel(this);
    inputLabel->setGeometry(20,10,80,20);
    inputLabel->setText("input");

    inputText = new QLineEdit(this);
    inputText->setGeometry(70,10,180,20);
    inputText->setText("MyServer");

    outputLabel = new QLabel(this);
    outputLabel->setGeometry(20,40,80,20);
    outputLabel->setText("output");

    outputText = new QLineEdit(this);
    outputText->setGeometry(70,40,180,20);

    msgLabel = new QLabel(this);
    msgLabel->setGeometry(20,70,80,20);
    msgLabel->setText("message");

    msgText = new QLineEdit(this);
    msgText->setGeometry(70,70,180,20);

    connectBtn = new QPushButton(this);
    connectBtn->setGeometry(20,110,80,30);
    connectBtn->setText("connect");

    sendMsgBtn = new QPushButton(this);
    sendMsgBtn->setGeometry(110,110,80,30);
    sendMsgBtn->setText("sendMsg");

    disconnectBtn = new QPushButton(this);
    disconnectBtn->setGeometry(200,110,80,30);
    disconnectBtn->setText("disconnect");

    connect(connectBtn, SIGNAL(clicked(bool)), this, SLOT(sl_connect()));
    connect(sendMsgBtn, SIGNAL(clicked(bool)), this, SLOT(sl_sendMsg()));
    connect(disconnectBtn, SIGNAL(clicked(bool)), this, SLOT(sl_disconnect()));

    localSocket = new QLocalSocket(this);
    connect(localSocket, SIGNAL(readyRead()), this, SLOT(sl_readyRead()));

    inputLabel2 = new QLabel(this);
    inputLabel2->setGeometry(20,180,80,20);
    inputLabel2->setText("input2");

    inputText2 = new QLineEdit(this);
    inputText2->setGeometry(70,180,180,20);
    inputText2->setText("MyServer");

    outputLabel2 = new QLabel(this);
    outputLabel2->setGeometry(20,210,80,20);
    outputLabel2->setText("output2");

    outputText2 = new QLineEdit(this);
    outputText2->setGeometry(70,210,180,20);

    msgLabel2 = new QLabel(this);
    msgLabel2->setGeometry(20,250,80,20);
    msgLabel2->setText("message2");

    msgText2 = new QLineEdit(this);
    msgText2->setGeometry(70,250,180,20);

    connectBtn2 = new QPushButton(this);
    connectBtn2->setGeometry(20,290,80,30);
    connectBtn2->setText("connect2");

    sendMsgBtn2 = new QPushButton(this);
    sendMsgBtn2->setGeometry(110,290,80,30);
    sendMsgBtn2->setText("sendMsg2");

    disconnectBtn2 = new QPushButton(this);
    disconnectBtn2->setGeometry(200,290,80,30);
    disconnectBtn2->setText("disconnect2");

    connect(connectBtn2, SIGNAL(clicked(bool)), this, SLOT(sl_connect2()));
    connect(sendMsgBtn2, SIGNAL(clicked(bool)), this, SLOT(sl_sendMsg2()));
    connect(disconnectBtn2, SIGNAL(clicked(bool)), this, SLOT(sl_disconnect2()));

    localSocket2 = new QLocalSocket(this);
    connect(localSocket2, SIGNAL(readyRead()), this, SLOT(sl_readyRead2()));

    crashBtn = new QPushButton(this);
    crashBtn->setGeometry(20,340,80,30);
    crashBtn->setText("crash");
    connect(crashBtn, SIGNAL(clicked(bool)), this, SLOT(sl_crash()));
}

Widget::~Widget()
{
    delete inputLabel;
    delete msgLabel;
    delete outputLabel;
    delete inputText;
    delete msgText;
    delete outputText;
    delete connectBtn;
    delete sendMsgBtn;
    delete disconnectBtn;
    delete localSocket;

    delete inputLabel2;
    delete msgLabel2;
    delete outputLabel2;
    delete inputText2;
    delete msgText2;
    delete outputText2;
    delete connectBtn2;
    delete sendMsgBtn2;
    delete disconnectBtn2;
    delete localSocket2;
}

QString Widget::getInputText(){
    return inputText->text();
}

void Widget::setOutputText(QString opText){
    outputText->setText(opText);
}

QString Widget::getMsgText(){
    return msgText->text();
}

void Widget::sl_connect(){
    QString serverName = getInputText();
    localSocket->connectToServer(serverName);
    if(localSocket->waitForConnected(1000)){
        setOutputText("Connected");
        qDebug() << "Connect to " + serverName + " succeed.";
    }else{
        setOutputText("Connect failed");
        qDebug() << "Connect to " + serverName + " failed";
    }
}

void Widget::sl_sendMsg(){
    if(localSocket->isValid()){
//        int val = 0;
//        while(1){
//            QString msg = getMsgText() + QString::number(val);
//            if(localSocket->write(msg.toUtf8()) == -1){
//                qDebug() << "An error occurred.Send message failed.";
//            }else{
//                qDebug() << "Send message succeed " << msg;
//            }
//            localSocket->flush();
//            val++;
//        }
        QString msg = getMsgText();// + QString::number(val);
        if(localSocket->write(msg.toUtf8()) == -1){
            qDebug() << "An error occurred.Send message failed.";
        }else{
            qDebug() << "Send message succeed " << msg;
        }
        localSocket->flush();

    }else{
        qDebug() << "Does not connect to any Servers";
    }
}

void Widget::sl_disconnect(){
    localSocket->disconnectFromServer();
//    qDebug() << localSocket->state();
    if(localSocket->state() == QLocalSocket::UnconnectedState){
        setOutputText("Disonnected");
    }else{
        setOutputText("Disonnect failed");
    }
}

void Widget::sl_readyRead(){
    qDebug() << "localSocket1 : " << localSocket->readAll();
}

QString Widget::getInputText2(){
    return inputText2->text();
}

void Widget::setOutputText2(QString opText){
    outputText2->setText(opText);
}

QString Widget::getMsgText2(){
    return msgText2->text();
}

void Widget::sl_connect2(){
    QString serverName = getInputText2();
    localSocket2->connectToServer(serverName);
    if(localSocket2->waitForConnected(1000)){
        setOutputText2("Connected");
        qDebug() << "LocalSocket2 connect to " + serverName + " succeed";
    }else{
        setOutputText2("Connect failed");
        qDebug() << "LocalSocket2 connect to " + serverName + " failed";
    }
}

void Widget::sl_sendMsg2(){
    if(localSocket2->isValid()){
        QString msg = getMsgText2();
        if(localSocket2->write(msg.toUtf8()) == -1){
            qDebug() << "An error occurred.Send message failed.";
        }else{
            qDebug() << "Send message succeed " << msg;
        }
        localSocket2->flush();
    }else{
        qDebug() << "Does not connect to any Servers";
    }
}

void Widget::sl_disconnect2(){
    localSocket2->disconnectFromServer();
    if(localSocket2->state() == QLocalSocket::UnconnectedState){
        setOutputText("Disonnected");
    }else{
        setOutputText("Disonnect failed");
    }
}

void Widget::sl_readyRead2(){
    qDebug() << "localSocket2 : " << localSocket2->readAll();
}

void Widget::sl_crash(){
    int i = 1/0;
}

