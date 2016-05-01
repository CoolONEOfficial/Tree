#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
#include <time.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    showFullScreen();

    srand(0);
    int random = rand()%100;
    if(random>50)
    {
        randomDirection = true;
    }
    else
    {
        randomDirection = false;
    }

    steps = ui->horizontalSlider->value();
    dirs = ui->horizontalSlider_2->value();
    size = 0;

    baseDir = QApplication::applicationDirPath();

    // Load Background
    background.load(baseDir+"\\images\\background.jpg");

    timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    num = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawTree(QPainter &p, int x1, int y1, int x2, int y2,int step)
{
    if(step>steps)
        return;


    if(step>steps-1)
    {
        p.setPen(QPen(QColor(0,175,0),1+size/40-(steps/40.0)));
        QBrush brush;
        brush.setColor(Qt::green);
        p.setBrush(brush);
    }
    else
    {
        p.setPen(QPen(QColor(150-step*3, 75-step*3, 0), 2+size/20.0-(steps)));
    }

    p.drawLine(x1,y1,x2-10+rand()%20+step*5,y2-10+rand()%20);

    int vecX = x2-x1;
    int vecY = y2-y1;

    int perX = -vecY;
    int perY = vecX;

    int drawX1,drawY1,drawX2,drawY2;

    drawX1 = x1+vecX/3;
    drawY1 = y1+vecY/3;

    drawX2 = x2;
    drawY2 = y2;

    drawTree(p,drawX1,drawY1,drawX2,drawY2,step+1);

    for(int f = 2; f<=dirs; f++)
    {
        if(randomDirection)
        {
            drawX2 = x2 - perX/f;
            drawY2 = y2 - perY/f;

            drawTree(p,drawX1,drawY1,drawX2,drawY2,step+1);

            drawX2 = x2 + perX/f;
            drawY2 = y2 + perY/f;

            drawTree(p,drawX1,drawY1,drawX2,drawY2,step+1);
        }
        else
        {
            drawX2 = x2 + perX/f;
            drawY2 = y2 + perY/f;

            drawTree(p,drawX1,drawY1,drawX2,drawY2,step+1);

            drawX2 = x2 - perX/f;
            drawY2 = y2 - perY/f;

            drawTree(p,drawX1,drawY1,drawX2,drawY2,step+1);
        }
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.drawImage(QRect(0,0,width(),height()),background);

    drawTree(p, width()/2, height()/4*3, width()/2, (height()/4*3)-size,0);
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    steps = value/10.0*8;
    size = (value-4)*50;
    update();
}

void Widget::on_horizontalSlider_2_valueChanged(int value)
{
    dirs = value;
    update();
}

void Widget::on_checkBox_Animation_released()
{
    if(ui->checkBox_Animation->isChecked())
    {
        timer->start(200);
    }
    else
    {
        timer->stop();
    }
}
