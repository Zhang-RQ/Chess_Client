//
// Created by Zhang on 2021/8/17.
//

#ifndef CHESS_CLIENT_CHESSBOARD_H
#define CHESS_CLIENT_CHESSBOARD_H

#include <QObject>
#include <QLabel>
#include <QMessageBox>
#include "chess.h"
#include "mainwindow.h"

class MainWindow;
class Chess;

class ChessBoard : public QLabel{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent=nullptr);
    bool CheckAccessibility(int sx,int sy,int dx,int dy,int type);
    void DecodeBoard(const QByteArray& s);
    void setPlayerColor(int C);
    int getPlayerColor() const;
    bool getInTurn() const;
    void TurnBegin();
    void TurnEnd();
    void setpMainWindow(MainWindow *p);
    bool checkMineClear(int c) const;
    QByteArray EncodeBoard() const;
    void setRounds(int _rounds);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Chess *pChess[13][6],*Selected;
    bool InTurn;
    int PlayerColor,RemainSecond; //0 blue,1 red
    bool HandleTwoChessInteract(int sx,int sy,int dx,int dy);
    QTimer *pTimer1s;
    MainWindow *pMainWindow;
    int Rounds,TimeoutTimes;

public slots:
    void HandlePressChess(int x,int y);
    void AdmitDefeat();
};

#endif //CHESS_CLIENT_CHESSBOARD_H
