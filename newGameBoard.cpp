/* @mainpage PIC 10C Fall 2015
 @author Hao Pang
 @date Friday, Dec 4, 2015

 This is the code for homework No.10

 We finally build out own games!
 Mine is a matching game that you try to match up all pairs.
 */
#include "newgameboard.h"
#include "ui_newgameboard.h"
#include <iostream>
#include <vector>
#include <algorithm> //random_shuffle
#include <QImage>
#include <QVector>
#include <ctime>

newGameBoard::newGameBoard(QWidget *parent, size_t board_sz, QString board_style) :
    QWidget(parent),
    ui(new Ui::newGameBoard), size(board_sz), style(board_style)
{
    ui->setupUi(this);
    srand(time(0));
    size_t sizeh;
    size_t repeatHelp;
    if(size==4){sizeh=3;repeatHelp=5;}
    else if(size==6){sizeh=5;repeatHelp=6;}
    else{sizeh=6;repeatHelp=7;};
    this->setFixedSize(size*80+135,sizeh*80+110);
    QVBoxLayout *vert= new  QVBoxLayout;        //Setup a vertical layout
    QWidget* topWidget= new QWidget;            //The top widget of the layout
    QWidget* timeWidget = new QWidget;
    QWidget* bottomWidget= new QWidget;          //A horizontal layout for bottom widget
    QWidget* boosters = new QWidget;
    QWidget* bottomWidget_align= new QWidget;
    QHBoxLayout *horiz=new QHBoxLayout(topWidget);      //A horizontal layout for to
    QGridLayout *layout = new QGridLayout(bottomWidget);    //A layout for middle widget
    QHBoxLayout *timelayout = new QHBoxLayout(timeWidget);
    QVBoxLayout *boosters_layout= new  QVBoxLayout(boosters);   //Layout for boosters on the bottom right
    QHBoxLayout *layout_align = new QHBoxLayout(bottomWidget_align);    //Layout containing bottom widgets and boosters
    boosters->setFixedWidth(80);
    bottomWidget->setFixedHeight(sizeh*80);
    bottomWidget->setFixedWidth(size*80);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    QLabel *test= new QLabel("Matching Game!");   //Title of the board
    topWidget->setFixedHeight(40);

    //Setup for topright part
    mylabel *time = new mylabel(120);
    time->setFixedWidth(140);
    test->setAlignment(Qt::AlignCenter);
    horiz->addWidget(test,0,Qt::AlignRight);
    horiz->addWidget(time,0,Qt::AlignRight);
    QTimer* timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),time,SLOT(showTime()));
    timer->start(1000);
    connect(time,SIGNAL(noTime()),this,SLOT(GameOver()));
    connect(time,SIGNAL(noTime()),timer,SLOT(stop()));
    mylabel *addtime = new mylabel(30);
    addtime->setAlignment(Qt::AlignRight);
    //addtime->hide();
    timelayout->addWidget(addtime);
    timeWidget->setFixedHeight(10);


    //Actions
    QLabel *action=new QLabel("Actions:");
    boosters_layout->addWidget(action,0,Qt::AlignCenter);
    QPushButton *restart= new QPushButton("Restart");
    boosters_layout->addWidget(restart,0,Qt::AlignCenter);
    QPushButton *pause= new QPushButton("Pause");
    boosters_layout->addWidget(pause,0,Qt::AlignCenter);
    QPushButton *resume= new QPushButton("Resume");
    boosters_layout->addWidget(resume,0,Qt::AlignCenter);
    QPushButton *back= new QPushButton("Back");
    boosters_layout->addWidget(back,0,Qt::AlignCenter);
    if (size==4)
        connect(restart,SIGNAL(clicked(bool)),parent,SLOT(easy_game_begin()));
    else if (size==6)
        connect(restart,SIGNAL(clicked(bool)),parent,SLOT(medium_game_begin()));
    else
        connect(restart,SIGNAL(clicked(bool)),parent,SLOT(hard_game_begin()));
    connect(resume,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(pause,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    connect(back,SIGNAL(clicked(bool)),parent,SLOT(game_over()));


    //Boosters
    QLabel *booster=new QLabel("Boosters:");
    boosters_layout->addWidget(booster,0,Qt::AlignCenter);
    QPushButton *flip= new QPushButton("flip");
    boosters_layout->addWidget(flip,0,Qt::AlignCenter);
    QPushButton *moretime= new QPushButton("time");
    boosters_layout->addWidget(moretime,0,Qt::AlignCenter);
    connect(moretime,SIGNAL(clicked(bool)),addtime,SLOT(show_add_time()));
    connect(moretime,SIGNAL(clicked(bool)),time,SLOT(add_time()));


    //Style setup
    QLabel **label = new QLabel*[2*size*sizeh];       //Initialize labels, widgets, and layouts for the particles
    myWidget **widgets = new myWidget*[size*sizeh];
    QString filename;
    if (style=="chinese")
        filename=":/myFiles/chinese.jpg";
    else if (style=="anime")
        filename=":/myFiles/anime.jpg";
    else
        filename=":/myFiles/vista.jpg";
    QImage mypic(filename);
    int height=mypic.height();
    //int width=mypic.width();
    QPixmap pix;
    QImage subpic;
    int x,y,w,h;

    //Set icon images
    QString filename2=":/myFiles/icon.jpg";
    QString filename2_2=":/myFiles/pokemon.jpg";
    QString filename2_3=":/myFiles/scenery.jpg";
    QVector<QImage> imagevector1;
    QVector<QImage> imagevector2;
    QVector<QImage> imagevector3;
    QImage mypic2(filename2);
    for(int i=0;i<6;i++)
    {
        QImage icon = mypic2.copy(52+i*156,156,110,110);
        imagevector1.push_back(icon);
    }
    for(int i=0;i<6;i++)
    {
        QImage icon = mypic2.copy(52+i*156,311,110,110);
        imagevector1.push_back(icon);
    }
    QImage mypic2_2(filename2_2);
    int height_2 = mypic2_2.height();
    int width_2 = mypic2_2.width();
    for(int i=0;i<4;i++)
    {
        QImage icon = mypic2_2.copy(i*(width_2/4),0,width_2/4,height_2/3);
        imagevector2.push_back(icon);
    }
    for(int i=0;i<3;i++)
    {
        QImage icon = mypic2_2.copy(i*(width_2/4),height_2/3,width_2/4,height_2/3);
        imagevector2.push_back(icon);
    }
    for(int i=0;i<3;i++)
    {
        QImage icon = mypic2_2.copy(i*(width_2/4),2*height_2/3,width_2/4,height_2/3);
        imagevector2.push_back(icon);
    }
    QImage mypic2_3(filename2_3);
    int height_3 = mypic2_3.height();
    int width_3 = mypic2_3.width();
    for(int i=0;i<4;i++)
    {
        QImage icon = mypic2_3.copy(i*(width_3/4),0,width_3/4,height_3/4);
        imagevector3.push_back(icon);
    }
    for(int i=0;i<4;i++)
    {
        QImage icon = mypic2_3.copy(i*(width_3/4),height_3/4,width_3/4,height_3/4);
        imagevector3.push_back(icon);
    }

    //Random numbers   //////////
    size_t repeat=sizeh*(size/2)/repeatHelp+1;
    std::vector<size_t> v;
    for(size_t j=0;j<repeat;j++)
    {
        for (size_t i=1;i<repeatHelp+1;i++)
        {
            if (v.size()<sizeh*size)
            {
                v.push_back(i);
                v.push_back(i);
            }
        }
    }
    std::random_shuffle(v.begin(),v.end());
    //Setup for myWidgets widgets
    for (size_t i=0;i<(sizeh*size);i++)                  //Build each particle
    {

        label[i] = new QLabel;              //Each particle consists a square and a number
        label[i+sizeh*size] = new QLabel;

        h=height/sizeh;
        w=h;
        x=(i%size)*(w);
        y=(i/size)*(h);
        subpic=mypic.copy(x,y,w,h);
        QPixmap temp=QPixmap::fromImage(subpic);
        temp=temp.scaled(80,80,Qt::KeepAspectRatio);
        label[i]->setPixmap(temp);
        QPixmap temp1;
        if (style=="chinese")
            temp1 = QPixmap::fromImage(imagevector1[v[i]]);
        else if (style=="anime")
            temp1 = QPixmap::fromImage(imagevector2[v[i]]);
        else
            temp1 = QPixmap::fromImage(imagevector3[v[i]]);
        temp1 = temp1.scaled(55,55,Qt::KeepAspectRatio);
        label[i+sizeh*size]->setPixmap(temp1);

        widgets[i] = new myWidget(label[i],label[i+sizeh*size],v[i],size*sizeh);

        layout->addWidget(widgets[i],i/size,i%size);
    }
    for (size_t i=0;i<sizeh*size;i++)
    {
        connect(widgets[i],SIGNAL(win()),timer,SLOT(stop()));
        connect(widgets[i],SIGNAL(win()),this,SLOT(YouWin()));
        connect(pause, SIGNAL(clicked(bool)),widgets[i],SLOT(stop_click()));
        connect(resume, SIGNAL(clicked(bool)),widgets[i],SLOT(start_click()));
    }
    layout_align->addWidget(bottomWidget,0,Qt::AlignLeft);
    layout_align->addWidget(boosters,0,Qt::AlignRight);
    vert->addWidget(topWidget);
    vert->addWidget(timeWidget);
    vert->addWidget(bottomWidget_align);
    connect(flip, SIGNAL (released()), widgets[0], SLOT (flip_all()));
    connect(back,SIGNAL(clicked(bool)),widgets[0],SLOT(clear_vec()));
    this->setLayout(vert);
}

/*@Slot after the player loses the game
 */
void newGameBoard::GameOver()
{
    QWidget* gameOver = new QWidget();
    gameOver->setFixedWidth(400);
    QVBoxLayout* gmov=new QVBoxLayout();
    QLabel *title = new QLabel("Game Over!");
    title->setAlignment(Qt::AlignCenter);
    QFont title_font = title->font();
    title_font.setPointSize(20);
    title->setFont(title_font);
    gmov->addSpacing(30);
    gmov->addWidget(title);
    gmov->addSpacing(15);
    QLabel* content = new QLabel();
    QString txt = "Do you want to try it again?";
    content->setText(txt);
    content->setAlignment(Qt::AlignCenter);
    gmov->addWidget(content);
    gmov->addSpacing(20);
    QPushButton* yes = new QPushButton("Yes");
    QPushButton* no = new QPushButton("No");
    yes->setFixedWidth(50);
    no->setFixedWidth(50);
    QHBoxLayout* yorn = new QHBoxLayout();
    yorn->addWidget(yes);
    yorn->addWidget(no);
    if (size==4)
        connect(yes,SIGNAL(clicked(bool)),parent(),SLOT(easy_game_begin()));
    else if (size==6)
        connect(yes,SIGNAL(clicked(bool)),parent(),SLOT(medium_game_begin()));
    else
        connect(yes,SIGNAL(clicked(bool)),parent(),SLOT(hard_game_begin()));
    connect(yes,SIGNAL(clicked(bool)),gameOver,SLOT(close()));
    connect(no,SIGNAL(clicked(bool)),parent(),SLOT(game_over()));
    connect(no,SIGNAL(clicked(bool)),gameOver,SLOT(close()));
    gmov->addLayout(yorn);
    gmov->addSpacing(30);
    gameOver->setLayout(gmov);
    gameOver->show();
}

/*@Slot after the player win the game
 */
void newGameBoard::YouWin()
{
    QWidget* gameOver = new QWidget();
    gameOver->setFixedWidth(400);
    QVBoxLayout* gmov=new QVBoxLayout();
    QLabel *title = new QLabel("You Win!");
    title->setAlignment(Qt::AlignCenter);
    QFont title_font = title->font();
    title_font.setPointSize(20);
    title->setFont(title_font);
    gmov->addSpacing(30);
    gmov->addWidget(title);
    gmov->addSpacing(15);
    QLabel* content = new QLabel();
    QString txt = "What do you want to do next?";
    content->setText(txt);
    content->setAlignment(Qt::AlignCenter);
    gmov->addWidget(content);
    gmov->addSpacing(20);
    QPushButton* again = new QPushButton("Play it again");
    QPushButton* out = new QPushButton("Quit game");
    again->setFixedWidth(100);
    out->setFixedWidth(100);
    QHBoxLayout* yorn = new QHBoxLayout();
    yorn->addWidget(again);
    yorn->addWidget(out);
    if (size==4)
    {
        connect(again,SIGNAL(clicked(bool)),parent(),SLOT(easy_game_begin()));
        QPushButton* nextlevel = new QPushButton("Next level");
        yorn->addWidget(nextlevel);
        nextlevel->setFixedWidth(100);
        connect(nextlevel,SIGNAL(clicked(bool)),parent(),SLOT(medium_game_begin()));
        connect(nextlevel,SIGNAL(clicked(bool)),gameOver,SLOT(close()));
    }
    else if (size==6)
    {
        connect(again,SIGNAL(clicked(bool)),parent(),SLOT(medium_game_begin()));
        QPushButton* nextlevel = new QPushButton("Next level");
        yorn->addWidget(nextlevel);
        connect(nextlevel,SIGNAL(clicked(bool)),parent(),SLOT(hard_game_begin()));
        connect(nextlevel,SIGNAL(clicked(bool)),gameOver,SLOT(close()));
    }
    else
        connect(again,SIGNAL(clicked(bool)),parent(),SLOT(hard_game_begin()));
    connect(again,SIGNAL(clicked(bool)),gameOver,SLOT(close()));
    connect(out,SIGNAL(clicked(bool)),parent(),SLOT(game_over()));
    connect(out,SIGNAL(clicked(bool)),gameOver,SLOT(close()));
    gmov->addLayout(yorn);
    gmov->addSpacing(30);
    gameOver->setLayout(gmov);
    gameOver->show();
}


/*@Construct myLabel to display the time remaining
 */
mylabel::mylabel(int a)
{
    sec=a;
}

/*@Get the time remaining
 */
int mylabel::gettime()
{
    return sec;
}

/*@Displays the time
 */
void mylabel::showTime()
{
    int min=sec/60;
    QString minString=QString::number(min);
    QString secString;
    if(sec%60==0)
        secString="00";
    else if(sec%60>9)
        secString=QString::number(sec%60);
    else
        secString="0"+QString::number(sec%60);
    this->setText("Time Remaining: "+minString+":"+secString);
    if (sec>0)
        sec--;
    else if (sec==0)
        emit noTime();
}

/*@Add more time to the timer
 */
void mylabel::add_time()
{
    sec+=30;
}

/*@Hide the timer
 */
void mylabel::Hide()
{
    this->hide();
}

newGameBoard::~newGameBoard()
{
    delete ui;
}


