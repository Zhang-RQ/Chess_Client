//
// Created by Zhang on 2021/8/17.
//

#ifndef CHESS_CLIENT_CHESSBOARD_H
#define CHESS_CLIENT_CHESSBOARD_H

#include <QObject>
#include <QLabel>
#include "chess.h"

class Chess;

class ChessBoard : public QLabel{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent=nullptr);
    bool CheckAccessibility(int sx,int sy,int dx,int dy,int type);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Chess *pChess[13][6],*Selected;
    int PlayerColor; //0 blue,1 red
    void HandleTwoChessInteract(int sx,int sy,int dx,int dy);

public slots:
    void HandlePressChess(int x,int y);
};

#endif //CHESS_CLIENT_CHESSBOARD_H
