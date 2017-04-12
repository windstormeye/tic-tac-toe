#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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

    void isWin();
    void clearMapNum();

public slots:
    void btnClick();
    void ending();
    void radioBtnClick();
};

#endif // MAINWINDOW_H
