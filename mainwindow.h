#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "connectwidget.h"
#include <QtNetwork/QtNetwork>
#include "chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const char EndSign=(char)0xFF;

class ChessBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void ReportConnectResult(int result);
    void Handshake();
    void SetColor(int C,int First);
    void StartGame(int First);
    void BoardSynchronize(const QByteArray& s);
    bool HandShakeOK;
    void setLCDTime(int t);
    void SendEndGame(int result);
    void SendBoard();
    void EndGame(int result);
    void SwitchPlayer(int p);
    void SendFlip(int x,int y);
    void PublicLog(QString s);

private:
    ConnectWidget *pConnectWidget;
    Ui::MainWindow *ui;
    QAction *actionConnectToServer,*actionStart,*actionAdmitDefeat,*actionCreateConnection;
    QString ServerIP;
    QTcpSocket *pTSocket; //receiver
    ChessBoard *pBoard;

public slots:
    void ConnectToServer();
    void ReadyGame();
    void SaveIP(QString IP);
    void CreateConnection();
    void HandleTransmission();
    void Restart();

};
#endif // MAINWINDOW_H
