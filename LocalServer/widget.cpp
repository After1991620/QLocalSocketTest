#include "widget.h"
#include <QDebug>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(100,100,300,210);

    //clear memory
    memset(m_lstClient, 0x00, MAX_NUM_OF_CLI_IDX * sizeof(CLI_IDX));

    inputLabel = new QLabel(this);
    inputLabel->setGeometry(20,10,80,20);
    inputLabel->setText("input:");

    inputText = new QLineEdit(this);
    inputText->setGeometry(70,10,180,20);
    inputText->setText("MyServer");

    outputLabel = new QLabel(this);
    outputLabel->setGeometry(20,40,80,20);
    outputLabel->setText("output:");

    outputText = new QLineEdit(this);
    outputText->setGeometry(70,40,180,20);

    msgLabel = new QLabel(this);
    msgLabel->setGeometry(20,70,80,20);
    msgLabel->setText("message");

    msgText = new QLineEdit(this);
    msgText->setGeometry(70,70,180,20);

    listenBtn = new QPushButton(this);
    listenBtn->setGeometry(20,110,80,30);
    listenBtn->setText("listen");

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(110,110,80,30);
    closeBtn->setText("close");

    crashBtn = new QPushButton(this);
    crashBtn->setGeometry(200,110,80,30);
    crashBtn->setText("crash");

    connect(listenBtn, SIGNAL(clicked(bool)), this, SLOT(sl_listen()));
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(sl_close()));
    connect(crashBtn, SIGNAL(clicked(bool)), this, SLOT(sl_crash()));

    localserver = new QLocalServer(this);
    connect(localserver, SIGNAL(newConnection()), this, SLOT(sl_newConnection()));

    closeSocketBtn = new QPushButton(this);
    closeSocketBtn->setGeometry(20,170,80,30);
    closeSocketBtn->setText("disconnect");

    connect(closeSocketBtn, SIGNAL(clicked(bool)), this, SLOT(sl_disconnectFromServer()));

}

Widget::~Widget()
{
    delete inputLabel;
    delete outputLabel;
    delete inputText;
    delete outputText;
    delete listenBtn;
    delete closeBtn;
    delete crashBtn;
    delete localserver;
    delete localSocket;
    delete closeSocketBtn;
}

QString Widget::getInputText(){
    return inputText->text();
}

void Widget::setOutputText(QString opText){
    outputText->setText(opText);
}

void Widget::setMsgText(QString msg){
    msgText->setText(msg);
}

void Widget::sl_listen(){
    QString serverName = getInputText();
    QLocalServer::removeServer(serverName);
    if(localserver->listen(serverName)){
        setOutputText("Listen succeed");
        qDebug() << "Listen succeed";
    }else{
        setOutputText("Listen failed");
        qDebug() << "Listen failed";
    }
}

void Widget::sl_close(){
    localserver->close();
    if(localserver->isListening()){
        setOutputText("Remove listen failed");
        qDebug() << "Remove listen failed";
    }else{
        setOutputText("Remove listen succeed");
        qDebug() << "Remove listen succeed";
    }
}

void Widget::sl_crash(){
    int i = 1/0;
}

void Widget::sl_newConnection(){
//    QLocalSocket *newSocket = localserver->nextPendingConnection();
//    newSocket->connectToServer("MyServer");

    localSocket = localserver->nextPendingConnection();
    qDebug() << localSocket;
    qDebug() << "sl_newConnection" << localSocket->state();
    connect(localSocket, SIGNAL(readyRead()), this, SLOT(sl_readyRead()));

    connect(localSocket, SIGNAL(connected()), this, SLOT(sl_connect()));
    connect(localSocket, SIGNAL(disconnected()), this, SLOT(sl_disconnect()));
    connect(localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(sl_error(QLocalSocket::LocalSocketError)));
    connect(localSocket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)), this, SLOT(sl_stateChanged(QLocalSocket::LocalSocketState)));

}

void Widget::sl_readyRead(){
//    QLocalSocket *senderSocket = static_cast<QLocalSocket *>(sender());
    qDebug() << localSocket;
    if(!localSocket) return;
    QString msg;
    msg = localSocket->readAll();
    qDebug() << msg;
    setMsgText(msg);

    QString receive = "receive";

    localSocket->write(receive.toUtf8());
    localSocket->flush();
}

void Widget::sl_connect(){
    qDebug() << "A new connection";
}

void Widget::sl_disconnect(){
    qDebug() << "Disconnected";
}

void Widget::sl_error(QLocalSocket::LocalSocketError socketError){
    qDebug() << socketError;
}

void Widget::sl_stateChanged(QLocalSocket::LocalSocketState socketState){
    qDebug() << socketState;
}

void Widget::sl_disconnectFromServer(){
    qDebug() << "disconnectFromServer";
    localSocket->disconnectFromServer();
    localSocket->abort();
}



