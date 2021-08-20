#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HandShakeOK=false;

    pBoard=ui->label;
    pBoard->setpMainWindow(this);

    ui->lcdNumber->display(20);

    actionConnectToServer=new QAction(this);
    actionConnectToServer->setText("Connect to server");
    ui->menuConnect->addAction(actionConnectToServer);

    actionCreateConnection=new QAction(this);
    actionCreateConnection->setText("Create Connection");
    ui->menuConnect->addAction(actionCreateConnection);

    actionStart=new QAction(this);
    actionStart->setText("Start");
    ui->menuPlayt->addAction(actionStart);

    actionAdmitDefeat=new QAction(this);
    actionAdmitDefeat->setText("Admit defeat");
    ui->menuPlayt->addAction(actionAdmitDefeat);

    connect(actionConnectToServer,&QAction::triggered,this,&MainWindow::ConnectToServer);
    connect(actionCreateConnection,&QAction::triggered,this,&MainWindow::CreateConnection);
    connect(actionStart,&QAction::triggered,this, &MainWindow::ReadyGame);
    connect(actionAdmitDefeat,&QAction::triggered,pBoard,&ChessBoard::AdmitDefeat);

    connect(ui->pushButton,&QPushButton::clicked,actionStart,&QAction::triggered);
    connect(ui->pushButton_2,&QPushButton::clicked,actionAdmitDefeat,&QAction::triggered);
    connect(ui->pushButton_3,&QPushButton::clicked,actionCreateConnection,&QAction::triggered);

    pConnectWidget=new ConnectWidget;
    connect(pConnectWidget,&ConnectWidget::SaveIP,this,&MainWindow::SaveIP);

    pTSocket=new QTcpSocket(this);

    connect(pTSocket,&QTcpSocket::readyRead,this,&MainWindow::HandleTransmission);
    connect(pTSocket,&QTcpSocket::connected,[&](){ReportConnectResult(1);});
    connect(pTSocket,&QTcpSocket::disconnected,[&](){ReportConnectResult(2);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectToServer()
{
    pConnectWidget->show();
}

void MainWindow::ReadyGame()
{
    qDebug()<<"Start Game"<<Qt::endl;
    qDebug()<<ServerIP<<Qt::endl;
    if(HandShakeOK)
    {
        QByteArray msg;
        msg.append((char)3);
        pTSocket->write(msg);
    }
    else
    {
        QMessageBox::information(nullptr,"Please connect to server.","Please connect to server.");
    }
}

void MainWindow::SaveIP(QString IP)
{
    ServerIP=IP;
}

void MainWindow::ReportConnectResult(int result)
{
    if(result==0)
    {
        qDebug("Connect Failed");
    }
    if(result==1)
    {
        qDebug("Connect Successfully");
    }
    if(result==2)
    {
        qDebug("Disconnected!");
    }
}

void MainWindow::CreateConnection()
{
    if(ServerIP==QString())
        return ReportConnectResult(0);
    pTSocket->connectToHost(ServerIP,25333);
    qDebug()<<"Connecting "<<ServerIP<<Qt::endl;
}

void MainWindow::HandleTransmission()
{
    QByteArray msg=pTSocket->readAll();
    int Sign=(int)msg.constData()[0];
    switch(Sign)
    {
        case 0:Handshake();break;
        case 2:StartGame((int)msg.constData()[1]);break;
        case 4:SetColor((int)msg.constData()[1]);break;
        case 5:BoardSynchronize(msg);break;
        case 7:EndGame((int)msg.constData()[1]);break;
        default:;
    }
}

void MainWindow::Handshake()
{
    QByteArray msg;
    msg.append((char)1);
    pTSocket->write(msg);
    HandShakeOK=true;
}

void MainWindow::SetColor(int C)
{
    pBoard->setPlayerColor(C);
    if(C)
    {
        ui->label_4->setText("红");
        ui->label_4->setStyleSheet("color:red");
    }
    else
    {
        ui->label_4->setText("蓝");
        ui->label_4->setStyleSheet("color:blue");
    }
}

void MainWindow::StartGame(int First)
{
    if(First)
        pBoard->TurnBegin();
    pBoard->setRounds(0);
}

void MainWindow::BoardSynchronize(const QByteArray &s)
{
    pBoard->DecodeBoard(s);
}

void MainWindow::setLCDTime(int t)
{
    ui->lcdNumber->display(t);
}

void MainWindow::SendEndGame(int result)
{
    QByteArray msg;
    msg.append((char)8);
    pTSocket->write(msg);
}

void MainWindow::EndGame(int result)
{
    if(result)
        QMessageBox::information(nullptr,"Game Ended!","Game Ended! You Win!");
    else
        QMessageBox::information(nullptr,"Game Ended!","Game Ended! You Lose!");
}

void MainWindow::SendBoard()
{
    QByteArray msg=pBoard->EncodeBoard();
    pTSocket->write(msg);
}

void MainWindow::SwitchPlayer(int p)
{
    if(p==0)
        ui->label_6->setText("你");
    else
        ui->label_6->setText("对方");
}