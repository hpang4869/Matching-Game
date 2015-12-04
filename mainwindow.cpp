/* @mainpage PIC 10C Fall 2015
 @author Hao Pang
 @date Friday, Dec 4, 2015

 This is the code for homework No.10

 We finally build out own games!
 Mine is a matching game that you try to match up all pairs.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgameboard.h"
#include <iostream>

/*@Set the initial value of level and style to 4 and chinese respectively
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    level=4;
    style="chinese";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*@Choose the level of the game
 */
void MainWindow::on_easy_toggled(bool checked)
{
    if(checked)
        level=4;
}

void MainWindow::on_medium_toggled(bool checked)
{
    if(checked)
        level=6;
}

void MainWindow::on_hard_toggled(bool checked)
{
    if(checked)
        level=8;
}

/*@Choose the style of the game
 */
void MainWindow::on_chinese_toggled(bool checked)
{
    if(checked)
        style="chinese";
}

void MainWindow::on_anime_toggled(bool checked)
{
    if(checked)
        style="anime";
}

void MainWindow::on_vista_toggled(bool checked)
{
    if(checked)
        style="vista";
}

/*@Display the instruction
 */
void MainWindow::displayInstruction()
{
    QWidget* instruction = new QWidget();
    QVBoxLayout* instr=new QVBoxLayout();
    QLabel *title = new QLabel("Instruction");
    title->setAlignment(Qt::AlignCenter);
    QFont title_font = title->font();
    title_font.setPointSize(20);
    title->setFont(title_font);
    instr->addSpacing(50);
    instr->addWidget(title);
    instr->addSpacing(25);
    QLabel* content = new QLabel();
    QString txt = "      There are many cards with different images on the back side. Once you find a pair with same images, the pair disappears. "
                  "\n\nTry to match up all such pairs and clear the board! You can choose your the level and your favorite background style!\n"
                  "\n\n      The boosters are set on the bottom right part to help you win the game:\n"
                  "\n            (1)The button 'flip' will filp all images for 6 seconds.\n"
                  "\n            (2)The button 'time' will add 20 more seconds for you.\n";

    content->setText(txt);
    instr->addWidget(content);
    instr->addSpacing(50);
    instruction->setLayout(instr);
    instruction->show();
}

void MainWindow::on_instruction_clicked()
{
    displayInstruction();
}

/*@Start new game with repective level
 */
void MainWindow::easy_game_begin() {

    level=4;
    this->setsize();
    board = new newGameBoard(this,4,style);
    this->setCentralWidget(board);
}

void MainWindow::medium_game_begin(){
    level=6;
    this->setsize();
    board = new newGameBoard(this,6,style);
    this->setCentralWidget(board);
}

void MainWindow::hard_game_begin(){
    level=8;
    this->setsize();
    board = new newGameBoard(this,8,style);
    this->setCentralWidget(board);
}

/*@Going back to main window from game board
 */
void MainWindow::game_over() {

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(NULL);
    // Line above will delete the widget gracefully (no memory errors)

    // Display something which says that you lost, maybe display high score.

    // Reset the MainWindow with the initial startup screen
    setFixedSize(450,350);
    level=4;
    style="chinese";
    ui->setupUi(this);


}

/*@Reset the size of the window
 */
void MainWindow::setsize()
{
    if (level==4)
        this->setFixedSize(4*80+135,3*80+130);
    else if (level==6)
        this->setFixedSize(6*80+135,5*80+130);
    else
        this->setFixedSize(8*80+135,6*80+130);
}

/*@Start game with the corresponding level and style
 */
void MainWindow::on_start_clicked()
{
    this->setsize();
    board = new newGameBoard(this,level,style);
    this->setCentralWidget(board);
}

/*@Quit the game
 */
void MainWindow::on_quit_clicked()
{
    this->close();
}


