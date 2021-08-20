//
// Created by Zhang on 2021/8/17.
//

#ifndef CHESS_CLIENT_CHESS_H
#define CHESS_CLIENT_CHESS_H

#include <QLabel>
#include <QPOint>
#include <QMouseEvent>
#include "chessboard.h"

namespace CHESS_DEFAULT{
    const QString FileNames[]={":/resource/engineer_blue.png",
                               ":/resource/engineer_red.png",
                               ":/resource/Pcommander_blue.png",
                               ":/resource/Pcommander_red.png",
                               ":/resource/Ccommander_blue.png",
                               ":/resource/Ccommander_red.png",
                               ":/resource/Ycommander_blue.png",
                               ":/resource/Ycommander_red.png",
                               ":/resource/Tcommander_blue.png",
                               ":/resource/Tcommander_red.png",
                               ":/resource/brigadier_blue.png",
                               ":/resource/brigadier_red.png",
                               ":/resource/Scommander_blue.png",
                               ":/resource/Scommander_red.png",
                               ":/resource/Acommander_blue.png",
                               ":/resource/Acommander_red.png",
                               ":/resource/commander_blue.png",
                               ":/resource/commander_red.png",
                               ":/resource/mine_blue.png",
                               ":/resource/mine_red.png",
                               ":/resource/bomb_blue.png",
                               ":/resource/bomb_red.png",
                               ":/resource/placeholder.png", //22
                               ":/resource/placeholder_unknown.png"}; //23

    const int DefaultWidth=68,DefaultHeight=34;

    const QPoint Positions[13][6]={{},
                                   {QPoint(),QPoint(13,14),QPoint(120,14),QPoint(221,14),QPoint(324,14),QPoint(428,14)},
                                   {QPoint(),QPoint(13,61),QPoint(120,61),QPoint(221,61),QPoint(324,61),QPoint(428,61)},
                                   {QPoint(),QPoint(13,107),QPoint(120,107),QPoint(221,107),QPoint(324,107),QPoint(428,107)},
                                   {QPoint(),QPoint(13,154),QPoint(120,154),QPoint(221,154),QPoint(324,154),QPoint(428,154)},
                                   {QPoint(),QPoint(13,201),QPoint(120,201),QPoint(221,201),QPoint(324,201),QPoint(428,201)},
                                   {QPoint(),QPoint(13,249),QPoint(120,249),QPoint(221,249),QPoint(324,249),QPoint(428,249)},
                                   {QPoint(),QPoint(13,396),QPoint(120,396),QPoint(221,396),QPoint(324,396),QPoint(428,396)},
                                   {QPoint(),QPoint(13,443),QPoint(120,443),QPoint(221,443),QPoint(324,443),QPoint(428,443)},
                                   {QPoint(),QPoint(13,490),QPoint(120,490),QPoint(221,490),QPoint(324,490),QPoint(428,490)},
                                   {QPoint(),QPoint(13,537),QPoint(120,537),QPoint(221,537),QPoint(324,537),QPoint(428,537)},
                                   {QPoint(),QPoint(13,584),QPoint(120,584),QPoint(221,584),QPoint(324,584),QPoint(428,584)},
                                   {QPoint(),QPoint(13,630),QPoint(120,630),QPoint(221,630),QPoint(324,630),QPoint(428,630)}};
}

class ChessBoard;

class Chess : public QLabel{
    Q_OBJECT

public:
    explicit Chess(ChessBoard *pBoard,QWidget *parent=nullptr,int _type=22,int hidden=0);
    void setPos(int x,int y);
    void setType(int _type);
    void swapHide();
    void swapPress();
    void setPress(int x);
    bool CheckOnRailway() const;
    bool CheckEmpty() const;
    bool CheckHidden() const;
    int GetX() const;
    int GetY() const;
    int GetType() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    ChessBoard *pBoard;
    bool PressDown,Hidden;
    int type,x,y;
    QPixmap *Pmap;

signals:
    void ChessClicked(int x,int y);
};

#endif //CHESS_CLIENT_CHESS_H
