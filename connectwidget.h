//
// Created by Zhang on 2021/8/18.
//

#ifndef CHESS_CLIENT_CONNECTWIDGET_H
#define CHESS_CLIENT_CONNECTWIDGET_H

#include <QWidget>
#include <QString>
#include "iperrordialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ConnectWidget; }
QT_END_NAMESPACE

class ConnectWidget : public QWidget {
    Q_OBJECT

public:
    explicit ConnectWidget(QWidget *parent = nullptr);

    ~ConnectWidget() override;

private:
    Ui::ConnectWidget *ui;
    IPErrorDialog *pIPErrorDialog;

private slots:
    void EnterChar(char c);

signals:
    void SaveIP(QString IP);
};


#endif //CHESS_CLIENT_CONNECTWIDGET_H
