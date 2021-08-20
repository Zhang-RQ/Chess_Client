//
// Created by Zhang on 2021/8/19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IPErrorDialog.h" resolved

#include "iperrordialog.h"
#include "ui_IPErrorDialog.h"


IPErrorDialog::IPErrorDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::IPErrorDialog) {
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&QDialog::close);
}

IPErrorDialog::~IPErrorDialog() {
    delete ui;
}

