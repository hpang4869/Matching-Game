/* @mainpage PIC 10C Fall 2015
 @author Hao Pang
 @date Friday, Dec 4, 2015

 This is the code for homework No.10

 We finally build out own games!
 Mine is a matching game that you try to match up all pairs.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newgameboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//Public slots that are used when starting a new game
public slots:
    void easy_game_begin();
    void medium_game_begin();
    void hard_game_begin();
    void game_over();
    void setsize();

//Private slots that are used to determine which kind of game is selected
private slots:
    void displayInstruction();

    void on_easy_toggled(bool checked);

    void on_medium_toggled(bool checked);

    void on_hard_toggled(bool checked);

    void on_chinese_toggled(bool checked);

    void on_anime_toggled(bool checked);

    void on_vista_toggled(bool checked);

    void on_instruction_clicked();

    void on_start_clicked();

    void on_quit_clicked();

private:
    Ui::MainWindow *ui;
    newGameBoard* board;
    size_t level;
    QString style;
};

#endif // MAINWINDOW_H
