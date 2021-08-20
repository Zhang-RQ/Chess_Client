//
// Created by Zhang on 2021/8/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ConnectToServer.h" resolved

#include <QRegularExpression>
#include <QValidator>
#include <QMessageBox>
#include "connectwidget.h"
#include "ui_connectwidget.h"

ConnectWidget::ConnectWidget(QWidget *parent) :
QWidget(parent), ui(new Ui::ConnectWidget) {
    ui->setupUi(this);

    QRegularExpression rx(R"(^(25[0-5]|2[0-4]\d|[0-1]?\d?\d)(\.(25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3}$)");
    QValidator *val=new QRegularExpressionValidator(rx,ui->lineEdit);
    ui->lineEdit->setValidator(val);

    connect(ui->pushButton,&QPushButton::clicked,this,&ConnectWidget::close);
    connect(ui->pushButton_2,&QPushButton::clicked,this,[&](){
        if(!ui->lineEdit->hasAcceptableInput())
        {
            QMessageBox::information(nullptr,"IP Format Error","IP Format Error!");
            return;
        }
        emit SaveIP(ui->lineEdit->text());
        this->close();
    });
    connect(ui->pushButton_3,&QPushButton::clicked,this,[&](){this->EnterChar('1');});
    connect(ui->pushButton_7,&QPushButton::clicked,this,[&](){this->EnterChar('2');});
    connect(ui->pushButton_8,&QPushButton::clicked,this,[&](){this->EnterChar('3');});
    connect(ui->pushButton_4,&QPushButton::clicked,this,[&](){this->EnterChar('4');});
    connect(ui->pushButton_9,&QPushButton::clicked,this,[&](){this->EnterChar('5');});
    connect(ui->pushButton_10,&QPushButton::clicked,this,[&](){this->EnterChar('6');});
    connect(ui->pushButton_5,&QPushButton::clicked,this,[&](){this->EnterChar('7');});
    connect(ui->pushButton_11,&QPushButton::clicked,this,[&](){this->EnterChar('8');});
    connect(ui->pushButton_12,&QPushButton::clicked,this,[&](){this->EnterChar('9');});
    connect(ui->pushButton_13,&QPushButton::clicked,this,[&](){this->EnterChar('0');});
    connect(ui->pushButton_14,&QPushButton::clicked,this,[&](){this->EnterChar('.');});
    connect(ui->pushButton_6,&QPushButton::clicked,ui->lineEdit,&QLineEdit::backspace);
}

ConnectWidget::~ConnectWidget() {
    delete ui;
}

void ConnectWidget::EnterChar(char c)
{
    ui->lineEdit->insert((QString)c);
}

