#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#define COM -1
#define MAN 1
#define STEP 9
#define DRAW 0
#define ROW 3
#define COL 3
#define MAX_NUM 1000;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<QPushButton *> btnList;
private:
    Ui::MainWindow *ui;
    int gameType;    // 人人对战 = 1， 人机对战 = 0
    int _cirCleMapNum[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };
    int _crossMapNum[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    //棋盘
    int board[3][3] = {
        { 0,0,0 },
        { 0,0,0 },
        { 0,0,0 }
    };
    // 临时棋盘
    int tempBoard[3][3] = {
        { 0,0,0 },
        { 0,0,0 },
        { 0,0,0 }
    };

    struct Move
    {
        int x;
        int y;

    };

    //玩家
    int player = MAN;
    //最好的一步
    Move bestMove;
    //当前深度
    int currentDepth = 9;

    void isWin();
    void clearMapNum();

    int a_isWin();
    int a_evaluteMap();
    void a_makeMove(Move curMove);
    void a_unMakeMove(Move curMove);
    int a_getMoveList(Move moveList[]);
    int a_miniMaxsearch(int depth);
    void a_printBoard();
    void a_com_play();
    void a_man_play(QPushButton *btn);

public slots:
    void btnClick();
    void ending();
    void radioBtnClick();
};

#endif // MAINWINDOW_H
