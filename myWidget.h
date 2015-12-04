/* @mainpage PIC 10C Fall 2015
 @author Hao Pang
 @date Friday, Dec 4, 2015

 This is the code for homework No.10

 We finally build out own games!
 Mine is a matching game that you try to match up all pairs.
 */
#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVector>
#include <QTimer>
#include "newgameboard.h"


class myWidget : public QWidget
{
    Q_OBJECT
    //static variable used to manipulate flipping widgets
    static size_t two;    //Counts the number of 2 widgets clicked (i.e. click one widget, two=1; click another widget, two=0; then the third one, two=1; again)
    static QVector<myWidget*> vct;  //Stores the last two widgets clicked
    static QVector<myWidget*> vec;  //Stores the remaining widgets
    static QVector<myWidget*> all;  //Stores all widgets
public:
    myWidget(QLabel* w_1, QLabel* w_2, size_t id, size_t level);
    myWidget();
    void flip();
    void compare();

signals:
    void win();
public slots:
    void stop_click();
    void start_click();
    void Flip();
    void Hide();
    void Show();
    void flip_all();
    void clear_vec();
protected:
    virtual void mousePressEvent(QMouseEvent *event);

private:
    QHBoxLayout *horiz;
    QHBoxLayout *horiz1;
    QHBoxLayout *horiz2;
    QWidget* w1;
    QWidget* w2;
    size_t myid;
    size_t level;
    bool stop;
};

#endif // MYWIDGET_H
