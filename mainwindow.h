#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "connectwidget.h"
#include <QtNetwork/QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    ConnectWidget *pConnectWidget;
    Ui::MainWindow *ui;
    QAction *actionConnectToServer,*actionStart,*actionAdmitDefeat,*actionCreateConnection;
    QString ServerIP;
    QTcpServer *pTServer; //sender
    QTcpSocket *pTSocket; //receiver

public slots:
    void ConnectToServer();
    void StartGame();
    void AdmitDefeat();
    void SaveIP(QString IP);
};
#endif // MAINWINDOW_H
