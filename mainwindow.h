#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <QKeyEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QLabel * Qgrid[16];
    int * mapArray[16];
    int max;
    int win;
    int move;
    int score;
    int best;
    int grid[4][4];
    int bgrid[4][4];

public:
    void keyPressEvent(QKeyEvent *event);
    void showWindow();
    int randomInt(int);

    void spin();
    void right();
    void left();
    void up();
    void down();

    int endCheck();
    void startGrid();
    void backupGrid();
    void spawn();
    void findMax();
    int checkMove();
    void winDialog();
    void loseDialog();

private slots:
    void on_NewGameButton_clicked();

    void on_HelpButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
