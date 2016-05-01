#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QImage>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    int num;
    int steps;
    int dirs;
    int size;

    bool randomDirection;

    QString baseDir;
    QImage background;

    QTimer *timer;

    void drawTree(QPainter &p, int x1, int y1, int x2, int y2, int step);
    void paintEvent(QPaintEvent *);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_checkBox_Animation_released();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
