#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QLocalServer>
#include <QLocalSocket>

typedef enum{
    CI_EMAJE_S8,
    CI_EMAJE_S8C2,
    MAX_NUM_OF_CLI_IDX
}CLI_IDX;

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
    QPushButton *listenBtn;
    QPushButton *closeBtn;
    QPushButton *crashBtn;
    QLocalServer *localserver;

    QLocalSocket *localSocket;
    QPushButton *closeSocketBtn;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QString getInputText();
    void setOutputText(QString opText);
    void setMsgText(QString msg);

public slots:
    void sl_listen();
    void sl_close();
    void sl_crash();
    void sl_newConnection();
    void sl_readyRead();

    void sl_connect();
    void sl_disconnect();
    void sl_error(QLocalSocket::LocalSocketError socketError);
    void sl_stateChanged(QLocalSocket::LocalSocketState socketState);

    void sl_disconnectFromServer();

private:
    QLocalSocket* m_lstClient[MAX_NUM_OF_CLI_IDX];

};

#endif // WIDGET_H
