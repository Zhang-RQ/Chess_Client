//
// Created by Zhang on 2021/8/19.
//

#ifndef CHESS_CLIENT_IPERRORDIALOG_H
#define CHESS_CLIENT_IPERRORDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class IPErrorDialog; }
QT_END_NAMESPACE

class IPErrorDialog : public QDialog {
Q_OBJECT

public:
    explicit IPErrorDialog(QWidget *parent = nullptr);

    ~IPErrorDialog() override;

private:
    Ui::IPErrorDialog *ui;
};


#endif //CHESS_CLIENT_IPERRORDIALOG_H
