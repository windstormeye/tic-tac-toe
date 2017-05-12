#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <QLabel>
#include <QRadioButton>

using namespace std;

static bool isCircle;
int step = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("井字棋");
    setWindowIcon(QIcon(QStringLiteral("url(:/mainlogo.png);")));


    isCircle = true;

    int btnX = 0;
    int btnY = 0;
    int btnW = 100;
    int btnH = 100;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QPushButton *btn = new QPushButton(this);
            btnList.push_back(btn);
            btnX = j * 100;
            btnY = i * 100;
            btn->setGeometry(btnX, btnY, btnW, btnH);
            btn->setStyleSheet("border-image: url(:/000.png);");
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClick()));
        }
    }
    QPushButton *resetBtn = new QPushButton(this);
    resetBtn->setGeometry(315, 15, 70, 20);
    resetBtn->setText("重新开始");
    connect(resetBtn, SIGNAL(clicked(bool)), this, SLOT(ending()));

    QRadioButton *radioBtn1 = new QRadioButton("人人对战", this);
    radioBtn1->setStyleSheet({"color:rgb(0,205,0)"});
    radioBtn1->setGeometry(resetBtn->pos().x(), resetBtn->pos().y() + 30,100,30);
    radioBtn1->setChecked(true);
    gameType = 1;    // 默认为人人对战，修改默认模式在此修改游戏模式
    connect(radioBtn1, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick()));

    QRadioButton *radioBtn2 = new QRadioButton("人机对战", this);
    radioBtn2->setStyleSheet({"color:rgb(255,0,0)"});
    radioBtn2->setGeometry(radioBtn1->pos().x(), radioBtn1->pos().y() + 35, 100, 30);
    connect(radioBtn2, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnClick() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (gameType) {    // 人人对战
        isCircle = !isCircle;
        if (isCircle) {
            btn->setStyleSheet("border-image: url(:/111.png);");
            btn->setEnabled(false);
            int btnX = btn->pos().x() / 100;
            int btnY = btn->pos().y() / 100;
            _cirCleMapNum[btnX][btnY] = 1;
            isWin();
        } else {
            btn->setStyleSheet("border-image: url(:/222.png);");
            btn->setEnabled(false);
            int btnX = btn->pos().x() / 100;
            int btnY = btn->pos().y() / 100;
            _crossMapNum[btnX][btnY] = 1;
            isWin();
        }
    } else {
                a_man_play(btn);
                if (player == a_isWin()) {
                   QMessageBox::information(this, NULL, "牛逼牛逼，你赢了！🐂🐂🐂", QMessageBox::Ok);
                }
                currentDepth--;
                player = (player == COM) ? MAN : COM;
                a_com_play();
                if (player == a_isWin()) {
                   QMessageBox::information(this, NULL, "人类败在了计算机的脚下！🌶🐓", QMessageBox::Ok);
                }
                currentDepth--;
                player = (player == COM) ? MAN : COM;
        }
}

void MainWindow::isWin() {
    if ((_cirCleMapNum[0][0] && _cirCleMapNum[0][1] && _cirCleMapNum[0][2]) ||
        (_cirCleMapNum[1][0] && _cirCleMapNum[1][1] && _cirCleMapNum[1][2]) ||
        (_cirCleMapNum[2][0] && _cirCleMapNum[2][1] && _cirCleMapNum[2][2])) {
        QMessageBox::information(this, NULL, "圈赢了！你真是太弱鸡了👎👎👎", QMessageBox::Ok);
        ending();
    } else if ((_cirCleMapNum[0][0] && _cirCleMapNum[1][0] && _cirCleMapNum[2][0]) ||
               (_cirCleMapNum[0][1] && _cirCleMapNum[1][1] && _cirCleMapNum[2][1]) ||
               (_cirCleMapNum[0][2] && _cirCleMapNum[1][2] && _cirCleMapNum[2][2])) {
        QMessageBox::information(this, NULL, "圈赢了！你真是太弱鸡了👎👎👎", QMessageBox::Ok);
        ending();
    } else if ((_cirCleMapNum[0][0] && _cirCleMapNum[1][1] && _cirCleMapNum[2][2]) ||
               (_cirCleMapNum[0][2] && _cirCleMapNum[1][1] && _cirCleMapNum[2][0])) {
        QMessageBox::information(this, NULL, "圈赢了！你真是太弱鸡了👎👎👎", QMessageBox::Ok);
        ending();
    } else if ((_crossMapNum[0][0] && _crossMapNum[0][1] && _crossMapNum[0][2]) ||
               (_crossMapNum[1][0] && _crossMapNum[1][1] && _crossMapNum[1][2]) ||
               (_crossMapNum[2][0] && _crossMapNum[2][1] && _crossMapNum[2][2])) {
        QMessageBox::information(this, NULL, "叉赢了！你真是太弱鸡了👎👎👎", QMessageBox::Ok);
        ending();
    } else if ((_crossMapNum[0][0] && _crossMapNum[1][0] && _crossMapNum[2][0]) ||
               (_crossMapNum[0][1] && _crossMapNum[1][1] && _crossMapNum[2][1]) ||
               (_crossMapNum[0][2] && _crossMapNum[1][2] && _crossMapNum[2][2])) {
        QMessageBox::information(this, NULL, "叉赢了！你真是太弱鸡了👎👎👎", QMessageBox::Ok);
        ending();
    } else if ((_crossMapNum[0][0] && _crossMapNum[1][1] && _crossMapNum[2][2]) ||
               (_crossMapNum[0][2] && _crossMapNum[1][1] && _crossMapNum[2][0])) {
        QMessageBox::information(this, NULL, "叉赢了！你真是太弱鸡了👎👎👎", QMessageBox::Ok);
        ending();
    }
}

void MainWindow::ending() {
    QList<QPushButton *> ::iterator it;
    isCircle = true;
    for(it=btnList.begin();it!=btnList.end();it++)
    {
        QPushButton *btn = *it;    // 需要把迭代器转成QPushButton
        btn->setStyleSheet("border-image: url(:/000.png);");
        btn->setEnabled(true);
    }
    clearMapNum();
}

void MainWindow::clearMapNum() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            _cirCleMapNum[i][j] = 0;
            _crossMapNum[i][j] = 0;
            board[i][j] = 0;
            tempBoard[i][j] = 0;
        }
    }
    currentDepth = 9;
    player = MAN;
}

void MainWindow::radioBtnClick() {
    QRadioButton *btn = qobject_cast<QRadioButton*>(sender());
    if (btn->text() == "人人对战") {
        gameType = 1;
        ending();
    } else {
        gameType = 0;
        ending();
    }
}

// ------------AI逻辑部分-------------------------------------------


int MainWindow::a_isWin() {
    for (int i = 0; i < 3; i++)
        {
            if (board[i][0] + board[i][1] + board[i][2] == 3)
                return 1;
            else if (board[i][0] + board[i][1] + board[i][2] == -3)
                return -1;
        }
        // 判断竖向输赢
        for (int j = 0; j < 3; j++)
        {
            if (board[0][j] + board[1][j] + board[2][j] == 3)
                return 1;
            else if (board[0][j] + board[1][j] + board[2][j] == -3)
                return -1;
        }
        // 判断斜向输赢
        if (board[0][0] + board[1][1] + board[2][2] == 3 || board[0][2] + board[1][1] + board[2][0] == 3)
            return 1;
        else if (board[0][0] + board[1][1] + board[2][2] == -3 || board[0][2] + board[1][1] + board[2][0] == -3)
            return -1;
        else  return 0;

}

int MainWindow::a_evaluteMap() {
    int i, j;

       if (a_isWin() == COM)
           return MAX_NUM;//如果计算机赢了，返回最大值
       if (a_isWin() == MAN)
           return -MAX_NUM;//如果计算机输了，返回最小值

       int count = 0;//该变量用来表示评估函数的值
       //将棋盘中的空格填满自己的棋子，既将棋盘数组中的0变为1
       for (i = 0; i < 3; i++)
           for (j = 0; j < 3; j++)
           {
               if (board[i][j] == 0)
                   tempBoard[i][j] = COM;
               else
                   tempBoard[i][j] = board[i][j];
           }
       //电脑一方
       //计算每一行中有多少行的棋子连成3个的
       for (i = 0; i < 3; i++)
           count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
       for (i = 0; i < 3; i++)
           count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
       count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
       count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;

       //将棋盘中的空格填满对方的棋子，既将棋盘数组中的0变为-1
       for (i = 0; i < 3; i++)
           for (j = 0; j < 3; j++)
           {
               if (board[i][j] == 0)
                   tempBoard[i][j] = MAN;
               else tempBoard[i][j] = board[i][j];
           }
       //对方
       //计算每一行中有多少行的棋子连成3个的
       for (i = 0; i < 3; i++)
           count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
       for (i = 0; i < 3; i++)
           count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
       count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
       count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;

       // 返回的数因为包括了负数和整数，所以不会太大
       return count;

}

void MainWindow::a_makeMove(Move curMove) {
    board[curMove.x][curMove.y] = player;
    player = (player == COM) ? MAN : COM;
}

void MainWindow::a_unMakeMove(Move curMove) {
    board[curMove.x][curMove.y] = 0;
    player = (player == COM) ? MAN : COM;

}

int MainWindow::a_getMoveList(Move moveList[]) {
    int moveCount = 0;
        int i, j;
        for (i = 0; i < COL; i++)
        {
            for (j = 0; j < ROW; j++)
            {
                if (board[i][j] == 0)
                {
                    moveList[moveCount].x = i;
                    moveList[moveCount].y = j;
                    moveCount++;
                }

            }
        }
    return moveCount; //返回一共多少个空的位置
}

int MainWindow::a_miniMaxsearch(int depth) {
    int value;  //估值
       int bestValue = 0; //最好的估值
       int moveCount = 0;
       int i;
       Move moveList[9];//保存可以下子的位置
       // 如果在深度未耗尽之前赢了
       if (a_isWin() == COM || a_isWin() == MAN)
       {
           // 这里返回的评估函数值是给递归用的
           return a_evaluteMap();
       }
       //如果搜索深度耗尽
       if (depth == 0)
       {
           // 这里返回的评估函数值是给递归用的
           return a_evaluteMap();
       }

       // 如果在深度未耗尽并且都没赢。
       // 先给一个初始值
       if (COM == player) {
           bestValue = -MAX_NUM;
       }
       else if (MAN == player)
       {
           bestValue = MAX_NUM;
       }

       //深度未耗尽并且都没赢的情况下，电脑需要获取到棋盘中剩余的位置，并且找到某一个位置下子
       // 获取棋盘上一共还剩多少步
       moveCount = a_getMoveList(moveList);

       // 遍历棋盘上剩余的每一步，找到最优点
       for (i = 0; i < moveCount; i++)
       {
           // 拿到棋盘剩余棋格中的一个棋格
           Move curMove = moveList[i];

           // 假装下个子
           a_makeMove(curMove);
           // 假装下子完成后，调用miniMax。
           // 调用完成后，获取返回值2
           value = a_miniMaxsearch(depth - 1);
           // 把假装下子的棋格清空
           a_unMakeMove(curMove);

           if (player == COM)
           {
               if (value > bestValue)
               {
                   bestValue = value;
                   // 防止出现递归未完成时，也调用了最优点
                   // 当递归return到最初开启递归那层时，赋值最优点
                   if (depth == currentDepth)
                   {
                       bestMove = curMove;
                   }
               }
           }
           else if (player == MAN)
           {
               if (value < bestValue)
               {
                   bestValue = value;
                   if (depth == currentDepth)
                   {
                       bestMove = curMove;
                   }
               }
           }
       }
   return bestValue;
}

void MainWindow::a_com_play() {
    a_miniMaxsearch(currentDepth);    // 可以不需要接收返回的最好值，因为已经直接改掉了bestMove
    board[bestMove.x][bestMove.y] = COM;
    int place = (bestMove.x * 3) + bestMove.y;
    for (int i = 0; i < btnList.size(); i++) {
        if (i == place) {
            btnList[i]->setStyleSheet("border-image: url(:/222.png);");
            btnList[i]->setEnabled(false);
        }
    }
}

void MainWindow::a_man_play(QPushButton *btn) {
    int x = btn->pos().x() / 100;
    int y = btn->pos().y() / 100;
    board[y][x] = MAN;
    btn->setStyleSheet("border-image: url(:/111.png);");
    btn->setEnabled(false);

    int times = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0) {
                times ++;
            }
        }

    }
    qDebug ("%d", times);
    if (times == 9) {
        QMessageBox::information(this, NULL, "你居然跟冷冰冰的机器打平了...", QMessageBox::Ok);
    }
}
