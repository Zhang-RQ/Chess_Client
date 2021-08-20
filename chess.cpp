//
// Created by Zhang on 2021/8/17.
//

#include <QPainter>
#include <QPen>
#include "chess.h"

using namespace CHESS_DEFAULT;

const static std::pair<int,int> HQs[]={std::make_pair(3,2),std::make_pair(3,4),
                                       std::make_pair(4,3),std::make_pair(5,2),std::make_pair(5,4),
                                       std::make_pair(8,2),std::make_pair(8,4),
                                       std::make_pair(9,3),std::make_pair(10,2),std::make_pair(10,4)};

Chess::Chess(ChessBoard *_pBoard,QWidget *parent,int _type,int hidden):QLabel(parent)
{
    x=0,y=0;
    pBoard=_pBoard;
    type=_type;
    Hidden=hidden;
    if(!Hidden)
        Pmap=new QPixmap(FileNames[type]);
    else
        Pmap=new QPixmap(FileNames[25]);
    PressDown=false;
}

void Chess::setPos(int _x,int _y)
{
    x=_x;y=_y;
    this->setGeometry(Positions[x][y].x(), Positions[x][y].y(), DefaultWidth ,DefaultHeight);
    std::pair<int,int> T=std::make_pair(x,y);
    bool f=false;
    for(const std::pair<int,int>& HQ:HQs)
        f|=HQ==T;
    if(type>>1==12&&f)
        this->hide();
    else
        this->show();
    this->update();
}

void Chess::setType(int _type)
{
    Q_ASSERT((_type>=0)&&(_type<=25));
    type=_type;
    delete Pmap;
    if(!Hidden)
        Pmap=new QPixmap(FileNames[type]);
    else
        Pmap=new QPixmap(FileNames[25]);
}

void Chess::swapHide()
{
    Hidden^=1;
    delete Pmap;
    if(!Hidden)
        Pmap=new QPixmap(FileNames[type]);
    else
        Pmap=new QPixmap(FileNames[25]);
}

void Chess::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),*Pmap);
    if(PressDown)
    {
        QPainter FramePainter(this);
        FramePainter.setPen(QPen(Qt::green,3.0));
        painter.drawRect(this->rect());
    }
}

void Chess::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton&&pBoard->getInTurn())
    {
        if((type&1)==pBoard->getPlayerColor())
        {
            if(PressDown&&Hidden&&((type>>1)!=11))
            {
                swapHide();
                this->update();
                pBoard->TurnEnd();
                //send flip message to server
            }
            swapPress();
        }
        emit ChessClicked(x,y);
    }
}

void Chess::swapPress()
{
    PressDown^=1;
    this->update();
}

void Chess::setPress(int x)
{
    if(x!=PressDown)
        swapPress();
}

bool Chess::CheckOnRailway() const
{
    if(y==1||y==5)
        return 2<=x&&x<=11;
    else
        return x==2||x==6||x==7||x==11;
}

bool Chess::CheckEmpty() const
{
    return type==24;
}

bool Chess::checkHidden() const
{
    return Hidden;
}

int Chess::GetX() const
{
    return x;
}

int Chess::GetY() const
{
    return y;
}

int Chess::getType() const
{
    return type;
}