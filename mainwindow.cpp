#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <QLabel>
#include <QRadioButton>

using namespace std;

static bool isCircle;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("井字棋");

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
    } else {    // 人机对战

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
        }
    }
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
