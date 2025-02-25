#ifndef MAINWINDON_H
#define MAINWINDON_H

#include<QMainWindow>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QPainter>
#include<QPixmap>
#include<QLabel>
#include<QSound>
#include<QPropertyAnimation>
#include<QtWidgets>
#include<QTime>
#include<fstream>
#include<windows.h>
#include<QMediaPlayer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
        void countscore();
        bool start, end;
        double speed;
        bool keyleft;
        bool keyright;
        bool keyA;
        bool keyW;
        bool keyD;
        bool printA, printW, printD;
        bool gamestart;
        bool touchstair;
        void stairjump();
        void stairfall();
        void stairgenerate();
        int scoretemp;
        int score;
        int HP;
        int a, c, d, te, e, f;
        double b;
        int movingstairspeed;
        void brokengenerate();
        void monstergenerate();
        void itemgenerate();
        //void bulletgenerate();
        bool isbroken;
        bool isbullet, isnew, isprint;
        QVector<double> bullet_x, bullet_y, i, j;
        QVector<int> broken_x, broken_y;
        QVector<int> index, monsterindex, itemindex;
        QVector<int> monster_x, monster_y;
        QVector<int> item_x, item_y;
    protected:
        //void mouseMoveEvent(QMouseEvent *event);
        /*void mousePressEvent(QMouseEvent *event);
        void mouseEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);*/
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);
    private:
        double doo_x;
        double doo_y;
        int x;
        int y;
        int time;
        int timerID;
        QVector<int> X;
        QVector<int> Y;
        QPixmap move_pic;
        QLabel *mvst;
        QImage doodle, stairbasic, stairbroken, stairdisappear, background, page, jetpack, hat, spring, trampoline;
        QImage stairbroken2, stairbroken3, stairmoving, monster1, monster2, monster3, monster4, heart, bullet;
        QImage doodleH1, doodleH2, doodleH3, doodleH4;
        QString key;
        QPropertyAnimation *animation;
};
#endif