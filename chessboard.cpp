//
// Created by Zhang on 2021/8/17.
//

#include "chessboard.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <queue>
#include <utility>
#include <set>


const static std::pair<int,int> HQs[]={std::make_pair(3,2),std::make_pair(3,4),
                                       std::make_pair(4,3),std::make_pair(5,2),std::make_pair(5,4),
                                       std::make_pair(8,2),std::make_pair(8,4),
                                       std::make_pair(9,3),std::make_pair(10,2),std::make_pair(10,4)};

ChessBoard::ChessBoard(QWidget *parent): QLabel(parent)
{
    InTurn=false;
    PlayerColor=0;
    Selected=nullptr;
    for(int i=1;i<=12;i++)
    {
        for(int j=1;j<=5;j++)
        {
            pChess[i][j]=new Chess(this,this);
            pChess[i][j]->setPos(i,j);
            pChess[i][j]->setType((i+j)%21);
            //pChess[i][j]->setType(24);
            //pChess[i][j]->swapHide(); //set to hide
            pChess[i][j]->show();
            connect(pChess[i][j],&Chess::ChessClicked,this,&ChessBoard::HandlePressChess);
        }
    }
    pTimer1s=new QTimer(this);
    pTimer1s->setInterval(1000);
    connect(pTimer1s,&QTimer::timeout,[&]()
    {
        --RemainSecond;
        pMainWindow->setLCDTime(RemainSecond);
        if(RemainSecond==0)
            pMainWindow->Timeout(),TurnEnd();
        else
            pTimer1s->start();
    });
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap ChessBoard_Png(":/resource/chessboard_empty.png");
    painter.drawPixmap(this->rect(), ChessBoard_Png);
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->position()<<Qt::endl;
    //Disselect
    if(Selected!=nullptr)
    {
        Selected->swapPress();
        Selected=nullptr;
    }
}

void ChessBoard::HandlePressChess(int x, int y)
{
    if(!InTurn)
        return;
    if(Selected==nullptr)
    {
        if((pChess[x][y]->getType() & 1) == PlayerColor)
            Selected=pChess[x][y];
    }
    else
    {
        //handle move & attack
        if(Selected!=pChess[x][y])
            HandleTwoChessInteract(Selected->GetX(),Selected->GetY(),x,y);
        Selected->setPress(0);
        pChess[x][y]->setPress(0);
        Selected=nullptr;
    }
    qDebug("Handled %d %d nullptr:%d\n",x,y,Selected==nullptr);
}

void ChessBoard::HandleTwoChessInteract(int sx, int sy, int dx, int dy)
{
    //qDebug("(%d,%d) -> (%d,%d) Accessibility type0:%d, type1:%d",sx,sy,dx,dy, CheckAccessibility(sx,sy,dx,dy,0),
    //       CheckAccessibility(sx,sy,dx,dy,1));
    if(pChess[sx][sy]->checkHidden() || pChess[dx][dy]->checkHidden())
        return;
    if((pChess[sx][sy]->getType() & 1) != (pChess[dx][dy]->getType() & 1))
    {
        //attack
        if(!CheckAccessibility(sx,sy,dx,dy, pChess[sx][sy]->getType() >> 1 == 0))
            return;
        std::pair<int,int> D=std::make_pair(dx,dy);
        for(const std::pair<int,int>& HQ:HQs)
            if(D==HQ)
                return;
        int SLevel=std::min(9, pChess[sx][sy]->getType() >> 1),DLevel=std::min(9, pChess[dx][dy]->getType() >> 1);
        if(pChess[dx][dy]->getType()>>1==11)
        {
            if(checkMineClear(PlayerColor^1))
            {
                pChess[dx][dy]->setType(24);
                std::swap(pChess[sx][sy],pChess[dx][dy]);
                pChess[sx][sy]->setPos(sx,sy);
                pChess[dx][dy]->setPos(dx,dy);
                pMainWindow->SendWinGame();
            }
        }
        else if(SLevel==0&&pChess[dx][dy]->getType()>>1==9)
        {
            pChess[dx][dy]->setType(24);
            std::swap(pChess[sx][sy],pChess[dx][dy]);
            pChess[sx][sy]->setPos(sx,sy);
            pChess[dx][dy]->setPos(dx,dy);
        }
        else if(SLevel>DLevel)
        {
            pChess[dx][dy]->setType(24);
            std::swap(pChess[sx][sy],pChess[dx][dy]);
            pChess[sx][sy]->setPos(sx,sy);
            pChess[dx][dy]->setPos(dx,dy);
        }
        else if(SLevel<DLevel)
        {
            pChess[sx][sy]->setType(24);
            std::swap(pChess[sx][sy],pChess[dx][dy]);
            pChess[sx][sy]->setPos(sx,sy);
            pChess[dx][dy]->setPos(dx,dy);
        }
        else
        {
            pChess[sx][sy]->setType(24);
            pChess[dx][dy]->setType(24);
        }
    }
    if(pChess[dx][dy]->CheckEmpty())
    {
        //move
        if(CheckAccessibility(sx,sy,dx,dy, pChess[sx][sy]->getType() >> 1 == 0))
        {
            std::swap(pChess[sx][sy],pChess[dx][dy]);
            pChess[sx][sy]->setPos(sx,sy);
            pChess[dx][dy]->setPos(dx,dy);
        }
    }
}

//BFS
bool ChessBoard::CheckAccessibility(int sx, int sy, int dx, int dy, int type) //type==1 means Engineer
{
    if(abs(sx-dx)+abs(sy-dy)==1)
    {
        if(sx==dx)
            return true;
        const static std::pair<int,int> ExPoints[]={std::make_pair(6,2),std::make_pair(6,4),
                                                    std::make_pair(7,2),std::make_pair(7,4)};
        std::pair<int,int> S={sx,sy},D={dx,dy};
        bool f=false;
        for(const std::pair<int,int> t:ExPoints)
            f|=S==t||D==t;
        if(!f)
            return true;
    }
    if(abs(sx-dx)==1&&abs(sy-dy)==1)
    {
        std::pair<int,int> S={sx,sy},D={dx,dy};
        for(const std::pair<int,int> t:HQs)
            if(S==t||D==t)
                return true;
    }
    if(!pChess[sx][sy]->CheckOnRailway())
        return false;
    //move on railway
    static int dltx[4]={-1,0,1,0};
    static int dlty[4]={0,-1,0,1};
    if(!type&&sx!=dx&&sy!=dy)
        return false;
    std::queue<std::pair<int,int>> q;
    std::set<std::pair<int,int>> PassedPoints;
    q.push({sx,sy});
    while(!q.empty())
    {
        PassedPoints.insert(q.front());
        auto [x,y]=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            if(((x==6&&y==2)||(x==6&&y==4))&&i==2)
                continue;
            if(((x==7&&y==2)||(x==7&&y==4))&&i==0)
                continue;
            int nx=x+dltx[i],ny=y+dlty[i];
            if(nx==dx&&ny==dy)
                return true;
            if(1<=nx&&nx<=12&&1<=ny&&ny<=5&&
                pChess[nx][ny]->CheckEmpty()&&
                pChess[nx][ny]->CheckOnRailway()&&
                !PassedPoints.count({nx,ny}))
                q.push({nx,ny});
        }
    }
    return false;
}

void ChessBoard::DecodeBoard(const QByteArray& s)
{
    for(int x=1;x<=12;x++)
        for(int y=1;y<=5;y++)
        {
            int id=(x-1)*5+y;
            const int* Array=(const int*)s.constData();
            pChess[x][y]->setType(Array[id]>>1);
            pChess[x][y]->setHidden(Array[id]&1);
        }
}

void ChessBoard::setPlayerColor(int C)
{
    PlayerColor=C;
}

int ChessBoard::getPlayerColor() const
{
    return PlayerColor;
}

bool ChessBoard::getInTurn() const
{
    return InTurn;
}

void ChessBoard::TurnBegin()
{
    pTimer1s->start();
    RemainSecond=20;
    pMainWindow->setLCDTime(20);
    InTurn=true;
}

void ChessBoard::TurnEnd()
{
    InTurn=false;
}

void ChessBoard::setpMainWindow(MainWindow *p)
{
    pMainWindow=p;
}

bool ChessBoard::checkMineClear(int c) const
{
    for(int x=1;x<=12;x++)
        for(int y=1;y<=5;y++)
            if(pChess[x][y]->getType()==18+c)
                return false;
   return true;
}