/* @mainpage PIC 10C Fall 2015
 @author Hao Pang
 @date Friday, Dec 4, 2015

 This is the code for homework No.10

 We finally build out own games!
 Mine is a matching game that you try to match up all pairs.
 */
#include "mywidget.h"
#include "newgameboard.h"
#include <iostream>


size_t myWidget::two = 0;   //Counts the number of 2 widgets clicked (i.e. click one widget, two=1; click another widget, two=0; then the third one, two=1; again)
QVector<myWidget*> myWidget::vct;   //Stores the last two widgets clicked
QVector<myWidget*> myWidget::vec;   //Stores the remaining widgets
QVector<myWidget*> myWidget::all;   //Stores all widgets

/*@Setup private variables for my widget
 */
myWidget::myWidget(QLabel* w_1, QLabel* w_2, size_t id_0,size_t lv)
{
    stop=false;
    myid=id_0;
    level=lv;
    w1 = new QWidget;
    w2 = new QWidget;
    w1->setFixedWidth(80);
    w1->setFixedHeight(80);
    w2->setFixedWidth(80);
    w2->setFixedHeight(80);
    horiz1 = new QHBoxLayout(w1);
    horiz2 = new QHBoxLayout(w2);
    horiz=new QHBoxLayout(this);
    horiz1->addWidget(w_1);
    horiz2->addWidget(w_2);
    w2->hide();
    horiz->setSpacing(0);
    horiz->setContentsMargins(0,0,0,0);
    horiz->addWidget(w1);
    horiz->addWidget(w2);
    vec.append(this);
    all.append(this);
}

/*@Make the widget be/not able to click
 */
void myWidget::stop_click()
{
    stop=true;
}

void myWidget::start_click()
{
    stop=false;
}

/*@Compare the last two widgets to see if they are the same
 */
void myWidget::compare()
{
    if(vct[0]->myid!=vct[1]->myid)
    {
        QTimer::singleShot(400,vct[0],SLOT(Flip()));
        QTimer::singleShot(400,vct[1],SLOT(Flip()));
        vct.pop_back();
        vct.pop_back();
    }
    else if(vct[0]->myid==vct[1]->myid)
    {
        QTimer::singleShot(400,vct[0],SLOT(Hide()));
        QTimer::singleShot(400,vct[1],SLOT(Hide()));
        for(size_t i=0;i<2;i++)
        {
            vct.pop_back();
            vec.pop_back();
        }
        //std::cout << vec.size() << std::endl;
        if (vec.begin()==vec.end())
        {
            std::cout << "win" << std::endl;
            while(all.begin()!=all.end())
                all.pop_back();
            emit win();
        }
    }
}

/*@Check everytime when mouse clicks on a widget
 */
void myWidget::mousePressEvent(QMouseEvent *event)
{
    if (w1->isVisible() && stop==false)
    {
        this->flip();
        if (two==0)
        {
            vct.append(this);
            two++;
        }
        else if (two==1)
        {
            vct.append(this);
            this->compare();
            two--;
        }
    }
}

/*@Make the widget unvisible/visible
 */
void myWidget::Hide()
{
    w1->setVisible(false);
    w2->setVisible(false);
}
void myWidget::Show()
{
    QWidget* w3 = new QWidget;
    QLabel* label = new QLabel("You Win!");
    QHBoxLayout* layout = new QHBoxLayout(w3);
    layout->addWidget(label);
    horiz->addWidget(w3);
    w3->setVisible(true);
}

/*@Flip the widget when needed
 */
void myWidget::Flip()
{
    this->flip();
}

void myWidget::flip()
{
    if (w1->isVisible())
    {
        w1->hide();
        w2->show();
    }
    else if (w2->isVisible())
    {
        w2->hide();
        w1->show();
    }
}

/*@Flip all widgets when needed
 */
void myWidget::flip_all()
{
    int index=0;
    for (size_t i=0;i<all.size();i++)
    {
        if(all[i]->w1->isVisible())
        {
            index=1;
            break;
        }
    }
    if(index==1)
    {
        for (int i=0;i<all.size();i++)
        {
            all[i]->flip();
            QTimer::singleShot(6000,all[i],SLOT(Flip()));
        }
    }
}

/*@clear all static variables
 */
void myWidget::clear_vec()
{
    while(vec.begin()!=vec.end())
        vec.pop_back();
    while(all.begin()!=all.end())
        all.pop_back();
    while(vct.begin()!=vct.end())
        vct.pop_back();
    two=0;
}

