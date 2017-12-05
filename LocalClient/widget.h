#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLocalSocket>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QLabel *inputLabel;
    QLabel *msgLabel;
    QLabel *outputLabel;
    QLineEdit *inputText;
    QLineEdit *msgText;
    QLineEdit *outputText;
    QPushButton *connectBtn;
    QPushButton *sendMsgBtn;
    QPushButton *disconnectBtn;
    QLocalSocket *localSocket;

    QLabel *inputLabel2;
    QLabel *msgLabel2;
    QLabel *outputLabel2;
    QLineEdit *inputText2;
    QLineEdit *msgText2;
    QLineEdit *outputText2;
    QPushButton *connectBtn2;
    QPushButton *sendMsgBtn2;
    QPushButton *disconnectBtn2;
    QLocalSocket *localSocket2;

    QPushButton *crashBtn;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QString getInputText();
    void setOutputText(QString opText);
    QString getMsgText();

    QString getInputText2();
    void setOutputText2(QString opText);
    QString getMsgText2();

public slots:
    void sl_connect();
    void sl_sendMsg();
    void sl_disconnect();
    void sl_readyRead();

    void sl_connect2();
    void sl_sendMsg2();
    void sl_disconnect2();
    void sl_readyRead2();

    void sl_crash();

};

#endif // WIDGET_H
