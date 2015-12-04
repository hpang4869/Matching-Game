/* @mainpage PIC 10C Fall 2015
 @author Hao Pang
 @date Friday, Dec 4, 2015

 This is the code for homework No.10

 We finally build out own games!
 Mine is a matching game that you try to match up all pairs.
 */
#ifndef NEWGAMEBOARD_H
#define NEWGAMEBOARD_H
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPixmap>
#include<QString>
#include <iostream>
#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include "mywidget.h"

#include <QWidget>

namespace Ui {
class newGameBoard;
class mylabel;
}

class newGameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit newGameBoard(QWidget *parent = 0, size_t size=6, QString style="");
    ~newGameBoard();

public slots:
    void GameOver();
    void YouWin();
private:
    Ui::newGameBoard *ui;
    QWidget *Board;
    size_t size;
    QString style;
};

class mylabel : public QLabel
{
    Q_OBJECT
public:
    mylabel(int a);
    int gettime();

public slots:
    void Hide();
    void add_time();
    void show_add_time();
    void showTime();
signals:
    void noTime();
private:
    int sec;
};

#endif // NEWGAMEBOARD_H
