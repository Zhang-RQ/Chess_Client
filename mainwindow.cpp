#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    connect(actionStart,&QAction::triggered,this,&MainWindow::StartGame);
    connect(actionAdmitDefeat,&QAction::triggered,this,&MainWindow::AdmitDefeat);

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

void MainWindow::StartGame()
{
    qDebug()<<"Start Game"<<Qt::endl;
    qDebug()<<ServerIP<<Qt::endl;
}

void MainWindow::AdmitDefeat()
{
    qDebug()<<"Admit Defeat"<<Qt::endl;
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
        pTSocket->write("Hello Server!");
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
    pTSocket->connectToHost(ServerIP,23333);
    qDebug()<<"Connecting "<<ServerIP<<Qt::endl;
}

void MainWindow::HandleTransmission()
{
    QByteArray msg=pTSocket->readAll();
    qDebug()<<"Incoming transmission:"<<msg<<Qt::endl;
}