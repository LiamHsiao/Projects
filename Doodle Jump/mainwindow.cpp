#include"mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(540, 960);

    //setMouseTracking(true);

    time = 0;
    timerID = startTimer(10);//1sec timer
    doo_x = 230;
    doo_y = 840;
    X.push_back(210);
    Y.push_back(920);
    start = true;
    gamestart = false;
    end = false;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for(int i=1; i<11; i++)
    {
        X.push_back(qrand() % 420);
        Y.push_back(Y.at(i-1) - ((qrand()%151)+120));
    }
    keyleft = false;
    keyright = false;
    keyA = false;
    keyW = false;
    keyD = false;
    touchstair = false;
    scoretemp = 0;
    score = 0;
    speed = 25.298;
    HP = 3;
    isbroken = true;
    a = 0;
    b = 0;
    d = 0;
    te = 0;
    e = 0;
    f = 0;
    isnew = false;
    isprint = false;
    printA = false;
    printW = false;
    printD = false;
    bullet_x.push_back(-1);
    bullet_y.push_back(-1);
    movingstairspeed = 3;
    index.push_back(1);
    monsterindex.push_back(1);
    itemindex.push_back(1);
    broken_x.push_back(100);
    c = 0;
    for(int a=0; a<10; a++)
    {
        if(Y.at(a)-Y.at(a+1) >= 120)
        {
            broken_y.push_back((Y.at(a)+Y.at(a+1))/2);
            break;
        }
    }
    monster_x.push_back(1000);
    monster_y.push_back(1000);
    item_x.push_back(1000);
    item_y.push_back(1000);
    doodle.load("./dataset/images/doodleL.png");
    stairbasic.load("./dataset/images/stair-basic.png");
    stairbroken.load("./dataset/images/stair-broken1.png");
    stairbroken2.load("./dataset/images/stair-broken2.png");
    stairbroken3.load("./dataset/images/stair-broken3.png");
    stairmoving.load("./dataset/images/stair-blue.png");
    stairdisappear.load("./dataset/images/stair-disapear.png");
    jetpack.load("./dataset/images/item-jetpack.png");
    hat.load("./dataset/images/item-propeller-hat.png");
    doodleH1.load("./dataset/images/doodleH/doodleH1.png");
    doodleH2.load("./dataset/images/doodleH/doodleH2.png");
    doodleH3.load("./dataset/images/doodleH/doodleH3.png");
    doodleH4.load("./dataset/images/doodleH/doodleH4.png");
    spring.load("./dataset/images/item-spring1.png");
    trampoline.load("./dataset/images/item-trampoline1.png");
    bullet.load("./dataset/images/bullet.png");
    monster1.load("./dataset/images/monster1.png");
    monster2.load("./dataset/images/monster2.png");
    monster3.load("./dataset/images/monster3.png");
    monster4.load("./dataset/images/monster4.png");
    heart.load("./dataset/images/heart2.png");
    background.load("./dataset/images/background.png");
    page.load("./dataset/images/reference-start-interface.png");
}

void MainWindow::stairjump()
{   
        speed -= 1;
        doo_y -= speed;
        for(int i=0; i<Y.size(); i++)
        {
            if((doo_y+80 <= Y.at(i)+30) && (doo_y+80 >= Y.at(i)) && (doo_x >= (X.at(i) - 80)) && (doo_x <= (X.at(i)+120)) && (speed < 0))
            {
                QSound::play("./dataset/sounds/jump.wav");
                speed = 25.298;
            }
        }
}

void MainWindow::stairfall()
{
    if(doo_y <= 480)
    {
        doo_y = 480;
        for(int i=0; i<11; i++)
        {
            int j=Y.at(0);
            j += speed;
            Y.erase(Y.begin());
            Y.push_back(j);
        }
        int k = broken_y.at(0);
        k += speed;
        broken_y.erase(broken_y.begin());
        broken_y.push_back(k);
        int n = monster_y.at(0);
        n += speed;
        monster_y.erase(monster_y.begin());
        monster_y.push_back(n);
        int m = item_y.at(0);
        m += speed;
        item_y.erase(item_y.begin());
        item_y.push_back(m);
    }
}

void MainWindow::stairgenerate()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    
    for(int i=0; i<11; i++)
    {
        if(Y.at(i) > 960)
        {
            X.erase(X.begin()+i);
            X.push_back(qrand() % 420);
            Y.erase(Y.begin()+i);
            Y.push_back(Y.at(9) - ((qrand()%(151))+120));
        }
    }
}

void MainWindow::brokengenerate()
{
    for(int i=6; i<10; i++)
    {
        if(broken_y.at(0) > 960)
        {
            if((Y.at(i)-Y.at(i+1)) >= 120)
            {
                QTime time = QTime::currentTime();
                qsrand((uint)time.msec());
                broken_x.erase(broken_x.begin());
                broken_x.push_back(qrand() % 421);
                broken_y.erase(broken_y.begin());
                broken_y.push_back((Y.at(i)+Y.at(i+1))/2);
                if((score <= 9000)&&(score >= 6100))
                {
                    index.erase(index.begin());
                    index.push_back((qrand() % 2) + 1);
                }
                else if(score >= 9000)
                {
                    index.erase(index.begin());
                    index.push_back((qrand() % 3) + 1);
                }
            }
            break;
            
        }
    }
}

void MainWindow::monstergenerate()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    if(monster_y.at(0) >= 1020)
    {        
    int j = (qrand() % 4) + 7;
    monster_x.erase(monster_x.begin());
    monster_x.push_back(X.at(j));
    monster_y.erase(monster_y.begin());
    monster_y.push_back(Y.at(j));
    monsterindex.erase(monsterindex.begin());
    monsterindex.push_back((qrand() % 4) + 1);
    }
}

void MainWindow::itemgenerate()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    if(item_y.at(0) >= 1000)
    {        
        int k = (qrand() % 4) + 7;
        item_x.erase(item_x.begin());
        item_x.push_back(X.at(k));
        item_y.erase(item_y.begin());
        item_y.push_back(Y.at(k));
        if((score <= 9000)&&(score >= 6000))
        {
            itemindex.erase(itemindex.begin());
            itemindex.push_back((qrand() % 2) + 1);
        }
        else if((score <= 12000)&&(score >= 9000))
        {
            itemindex.erase(itemindex.begin());
            itemindex.push_back((qrand() % 3) + 1);
        }
        else if(score >= 12000)
        {
            itemindex.erase(itemindex.begin());
            itemindex.push_back((qrand() % 4) + 1);
        }
    }
}

void MainWindow::countscore()
{
    int temp = 960 - doo_y;
    if(temp >= scoretemp)
    {
        scoretemp = temp;
    }
    if(doo_y <= 480)
    {
        scoretemp += speed;
    }
    if(scoretemp >= score)
    {
        score = scoretemp;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Left) && (gamestart == true))
    {
        keyleft = true;
        update();//call paintEvent
    }
    else if((event->key() == Qt::Key_Right) && (gamestart == true))
    {
        keyright = true;
        update();//call paintEvent
    }
    else if((event->key() == Qt::Key_A) && (gamestart == true))
    {
        keyA = true;
        update();//call paintEvent
    }
    else if((event->key() == Qt::Key_W) && (gamestart == true))
    {
        keyW = true;
        update();//call paintEvent
    }
    else if((event->key() == Qt::Key_D) && (gamestart == true))
    {
        keyD = true;
        update();//call paintEvent
    }
    else if(event->key() == Qt::Key_P)
    {
        gamestart = true;
        start = false;
        end = false;
        doo_x = 230;
        doo_y = 840;
        X.erase(X.begin(), X.end());
        Y.erase(Y.begin(), Y.end());
        X.push_back(210);
        Y.push_back(920);
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        for(int i=1; i<11; i++)
        {
            X.push_back(qrand() % 420);
            Y.push_back(Y.at(i-1) - ((qrand()%151)+120));
        }
        keyleft = false;
        keyright = false;
        keyA = false;
        keyW = false;
        keyD = false;
        touchstair = false;
        scoretemp = 0;
        score = 0;
        speed = 25.298;
        HP = 3;
        isbroken = true;
        a = 0;
        b = 0;
        d = 0;
        te = 0;
        e = 0;
        f = 0;
        isnew = false;
        isprint = false;
        printA = false;
        printW = false;
        printD = false;
        bullet_x.erase(bullet_x.begin());
        bullet_x.push_back(-1);
        bullet_y.erase(bullet_y.begin());
        bullet_y.push_back(-1);
        movingstairspeed = 3;
        index.erase(index.begin());
        index.push_back(1);
        monsterindex.erase(monsterindex.begin());
        monsterindex.push_back(1);
        itemindex.erase(itemindex.begin());
        itemindex.push_back(1);
        broken_x.erase(broken_x.begin());
        broken_x.push_back(100);
        c = 0;
        broken_y.erase(broken_y.begin());
        for(int a=0; a<10; a++)
        {
            if(Y.at(a)-Y.at(a+1) >= 120)
            {
                broken_y.push_back((Y.at(a)+Y.at(a+1))/2);
                break;
            }
        }
        monster_x.erase(monster_x.begin());
        monster_x.push_back(1000);
        monster_y.erase(monster_y.begin());
        monster_y.push_back(1000);
        item_x.erase(item_x.begin());
        item_x.push_back(1000);
        item_y.erase(item_y.begin());
        item_y.push_back(1000);
            update();//call paintEvent
    }
    else if(event->key() == Qt::Key_R)
    {
        start = true;
        gamestart = false;
        end = false;
        update();//call paintEvent
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        keyleft = false;
    }
    if(event->key() == Qt::Key_Right)
    {
        keyright = false;
    }
     else if(event->key() == Qt::Key_A)
    {
        keyA = false;
        update();//call paintEvent
    }
    else if(event->key() == Qt::Key_W)
    {
        keyW = false;
        update();//call paintEvent
    }
    else if(event->key() == Qt::Key_D)
    {
        keyD = false;
        update();//call paintEvent
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    
    if(start == true)
    {
        gamestart = false;
        end = false;
        QPainter painter(this);
        QFont font;
        QPen pen;
        painter.drawImage(45, 180, page);
    }
    if(gamestart == true)
    {
        QPainter painter(this);
        QFont font;
        QPen pen;
        countscore();
        stairjump();
        stairfall();
        stairgenerate();
        painter.drawImage(0, 0, background);
        painter.setRenderHint(QPainter::Antialiasing, true);
        for(int i=0; i<11; i++)
        {
            painter.drawImage(X.at(i), Y.at(i), stairbasic);
        }
        brokengenerate();
        if(score <= 6000)
        {
            if(isbroken == true)
            {
                painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken);
                if((doo_y+80 <= broken_y.at(0)+30) && (doo_y+80 >= broken_y.at(0)) && (doo_x >= (broken_x.at(0) - 80)) && (doo_x <= (broken_x.at(0)+120)) && (speed < 0))
                {
                    painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken2);
                    painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken3); 
                    QSound::play("./dataset/sounds/break.wav");
                    broken_x.erase(broken_x.begin());
                    broken_y.erase(broken_y.begin());
                    broken_x.push_back(961);
                    broken_y.push_back(961);
                }
            }
        }
        else if(score < 9000)
        {
            if(isbroken == true){
                switch(index.at(0))
                {
                    case 1:
                        painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken);
                        if((doo_y+80 <= broken_y.at(0)+30) && (doo_y+80 >= broken_y.at(0)) && (doo_x >= (broken_x.at(0) - 80)) && (doo_x <= (broken_x.at(0)+120)) && (speed < 0))
                        {
                            painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken2);
                            painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken3);
                            QSound::play("./dataset/sounds/break.wav");
                            broken_x.erase(broken_x.begin());
                            broken_y.erase(broken_y.begin());
                            broken_x.push_back(961);
                            broken_y.push_back(961);
                        }
                        break;
                    case 2:
                        a=broken_x.at(0);
                        a += movingstairspeed;
                        if(a >= 420)
                        {
                            movingstairspeed = -3;
                        }
                        if(a <= 0)
                        {
                            movingstairspeed = 3;
                        }
                        broken_x.erase(broken_x.begin());
                        broken_x.push_back(a);
                        if((doo_y+80 <= broken_y.at(0)+30) && (doo_y+80 >= broken_y.at(0)) && (doo_x >= (broken_x.at(0) - 80)) && (doo_x <= (broken_x.at(0)+120)) && (speed < 0))
                        {
                            QSound::play("./dataset/sounds/jump.wav");
                            speed = 25.298;
                        }
                        painter.drawImage(broken_x.at(0), broken_y.at(0), stairmoving);
                        break;
                    default:
                        break;
                }
            }
        }
        else if(score >= 9000)
        {
            if(isbroken == true){
                switch(index.at(0))
                {
                    case 1:
                        painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken);
                        if((doo_y+80 <= broken_y.at(0)+30) && (doo_y+80 >= broken_y.at(0)) && (doo_x >= (broken_x.at(0) - 80)) && (doo_x <= (broken_x.at(0)+120)) && (speed < 0))
                        {
                            painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken2);
                            painter.drawImage(broken_x.at(0), broken_y.at(0), stairbroken3);
                            QSound::play("./dataset/sounds/break.wav");
                            broken_x.erase(broken_x.begin());
                            broken_y.erase(broken_y.begin());
                            broken_x.push_back(961);
                            broken_y.push_back(961);
                        }
                        break;
                    case 2:
                        a=broken_x.at(0);
                        a += movingstairspeed;
                        if(a >= 420)
                        {
                            movingstairspeed = -3;
                        }
                        if(a <= 0)
                        {
                            movingstairspeed = 3;
                        }
                        broken_x.erase(broken_x.begin());
                        broken_x.push_back(a);
                        if((doo_y+80 <= broken_y.at(0)+30) && (doo_y+80 >= broken_y.at(0)) && (doo_x >= (broken_x.at(0) - 80)) && (doo_x <= (broken_x.at(0)+120)) && (speed < 0))
                        {
                            QSound::play("./dataset/sounds/jump.wav");
                            speed = 25.298;
                        }
                        painter.drawImage(broken_x.at(0), broken_y.at(0), stairmoving);
                        break;
                    case 3:
                        if((doo_y+80 <= broken_y.at(0)+30) && (doo_y+80 >= broken_y.at(0)) && (doo_x >= (broken_x.at(0) - 80)) && (doo_x <= (broken_x.at(0)+120)) && (speed < 0))
                        {
                            QSound::play("./dataset/sounds/jump.wav");
                            speed = 25.298;
                            broken_x.erase(broken_x.begin());
                            broken_x.push_back(961);
                            broken_y.erase(broken_y.begin());
                            broken_y.push_back(961);
                        }
                        painter.drawImage(broken_x.at(0), broken_y.at(0), stairdisappear);
                        break;
                    default:
                        break;
                }
            }
        }

        itemgenerate();
        if((score < 6000)&&(score > 3000))
        {
            if(isbroken == true)
            {
                if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 25) && (doo_x + 80 >= (item_x.at(0) + 40)) && (doo_x <= (item_x.at(0)+80)) && (speed < 0))
                {
                    QSound::play("./dataset/sounds/spring.wav");
                    speed = 43.818;
                }
                painter.drawImage(item_x.at(0)+40, item_y.at(0)-25, spring);
            }
        }
        else if((score < 9000)&&(score > 6000))
        {
            if(isbroken == true)
            {
                switch(itemindex.at(0))
                {
                    case 1:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 25) && (doo_x + 80 >= (item_x.at(0) + 40)) && (doo_x <= (item_x.at(0)+80)) && (speed < 0))
                    {
                        QSound::play("./dataset/sounds/spring.wav");
                        speed = 43.818;
                    }
                        painter.drawImage(item_x.at(0)+40, item_y.at(0)-25, spring);
                        break;
                    case 2:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 36) && (doo_x + 80 >= (item_x.at(0) + 24)) && (doo_x <= (item_x.at(0)+96)) && (speed < 0))
                        {
                            QSound::play("./dataset/sounds/trampoline.wav");
                            speed = 61.968;
                        }
                        painter.drawImage(item_x.at(0)+24, item_y.at(0)-36, trampoline);
                        break;
                    default:
                        break;
                }
            }
        }
        else if((score < 12000)&&(score > 9000))
        {
            if(isbroken == true)
            {
                switch(itemindex.at(0))
                {
                    case 1:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 25) && (doo_x + 80 >= (item_x.at(0) + 40)) && (doo_x <= (item_x.at(0)+80)) && (speed < 0))
                    {
                        QSound::play("./dataset/sounds/spring.wav");
                        speed = 43.818;
                    }
                        painter.drawImage(item_x.at(0)+40, item_y.at(0)-25, spring);
                        break;
                    case 2:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 36) && (doo_x + 80 >= (item_x.at(0) + 24)) && (doo_x <= (item_x.at(0)+96)) && (speed < 0))
                        {
                            QSound::play("./dataset/sounds/trampoline.wav");
                            speed = 61.968;
                        }
                        painter.drawImage(item_x.at(0)+24, item_y.at(0)-36, trampoline);
                        break;
                    case 3:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 40) && (doo_x + 80 >= (item_x.at(0) + 28)) && (doo_x <= (item_x.at(0)+92)) )
                        {
                            QSound::play("./dataset/sounds/propeller.wav");
                            speed = 87.6356;
                            painter.drawImage(doo_x, doo_y, doodleH1);
                            painter.drawImage(doo_x, doo_y, doodleH2);
                            painter.drawImage(doo_x, doo_y, doodleH3);
                            painter.drawImage(doo_x, doo_y, doodleH4);
                        }
                        painter.drawImage(item_x.at(0)+28, item_y.at(0)-40, hat);
                        break;
                    default:
                        break;
                }
            }
        }
        else if(score >= 12000)
        {
            if(isbroken == true)
            {
                switch(itemindex.at(0))
                {
                    case 1:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 25) && (doo_x + 80 >= (item_x.at(0) + 40)) && (doo_x <= (item_x.at(0)+80)) && (speed < 0))
                    {
                        QSound::play("./dataset/sounds/spring.wav");
                        speed = 43.818;
                    }
                        painter.drawImage(item_x.at(0)+40, item_y.at(0)-25, spring);
                        break;
                    case 2:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 36) && (doo_x + 80 >= (item_x.at(0) + 24)) && (doo_x <= (item_x.at(0)+96)) && (speed < 0))
                        {
                            QSound::play("./dataset/sounds/trampoline.wav");
                            speed = 61.968;
                        }   
                        painter.drawImage(item_x.at(0)+24, item_y.at(0)-36, trampoline);
                        break;
                    case 3:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 40) && (doo_x + 80 >= (item_x.at(0) + 28)) && (doo_x <= (item_x.at(0)+92)))
                        {
                            QSound::play("./dataset/sounds/propeller.wav");
                            speed = 87.6356;
                        }
                        painter.drawImage(item_x.at(0)+28, item_y.at(0)-40, hat);
                        break;
                    case 4:
                        if((doo_y+80 <= item_y.at(0)) && (doo_y+80 >= item_y.at(0) - 72) && (doo_x + 80 >= (item_x.at(0) + 35)) && (doo_x <= (item_x.at(0) + 85)))
                        {
                            QSound::play("./dataset/sounds/rocket.wav");
                            speed = 123.935;
                        }
                        painter.drawImage(item_x.at(0)+35, item_y.at(0)-72, jetpack);
                        break;
                    default:
                        break;
                }
            }
        }
        
        monstergenerate();
        if(isbroken == true)
        {
            switch(monsterindex.at(0))
            {
            case 1:
                if((doo_y+80 <= monster_y.at(0) - 45) && (doo_y+80 >= monster_y.at(0) - 75) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed < 0))
                {
                    QSound::play("./dataset/sounds/jumponmonster.wav");
                    speed = 25.298;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((bullet_x.at(0) + 20 >= monster_x.at(0)) && (bullet_x.at(0) <= monster_x.at(0) + 120) && (bullet_y.at(0) <= monster_y.at(0) ) && (bullet_y.at(0) >= (monster_y.at(0) - 75)))
                {
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((doo_y+80 <= monster_y.at(0)) && (doo_y+80 >= monster_y.at(0) - 45) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed > 0) && (speed <= 25.298))
                {
                    HP--;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                painter.drawImage(monster_x.at(0), monster_y.at(0)-75, monster1);
                break;
            case 2:
                if((doo_y+80 <= monster_y.at(0) - 137) && (doo_y+80 >= monster_y.at(0) - 167) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed < 0))
                {
                    QSound::play("./dataset/sounds/jumponmonster.wav");
                    speed = 25.298;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((bullet_x.at(0) + 20 >= monster_x.at(0)) && (bullet_x.at(0) <= monster_x.at(0) + 120) && (bullet_y.at(0) <= monster_y.at(0) ) && (bullet_y.at(0) >= (monster_y.at(0) -167)))
                {
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((doo_y+80 <= monster_y.at(0)) && (doo_y+80 >= monster_y.at(0) - 100) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed > 0) && (speed <= 25.298))
                {
                    HP--;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                painter.drawImage(monster_x.at(0), monster_y.at(0)-167, monster2);
                break;
            case 3:
                if((doo_y+80 <= monster_y.at(0) - 45) && (doo_y+80 >= monster_y.at(0) - 75) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed < 0))
                {
                    QSound::play("./dataset/sounds/jumponmonster.wav");
                    speed = 25.298;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((bullet_x.at(0) + 20 >= monster_x.at(0)) && (bullet_x.at(0) <= monster_x.at(0) + 120) && (bullet_y.at(0) <= monster_y.at(0) ) && (bullet_y.at(0) >= (monster_y.at(0) - 75)))
                {
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((doo_y+80 <= monster_y.at(0)) && (doo_y+80 >= monster_y.at(0) - 45) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed > 0) && (speed <= 25.298))
                {
                    HP--;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                painter.drawImage(monster_x.at(0), monster_y.at(0)-75, monster3);
                break;
            case 4:
                if((doo_y+80 <= monster_y.at(0) - 38) && (doo_y+80 >= monster_y.at(0) - 68) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed < 0))
                {
                    QSound::play("./dataset/sounds/jumponmonster.wav");
                    speed = 25.298;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((bullet_x.at(0) + 20 >= monster_x.at(0)) && (bullet_x.at(0) <= monster_x.at(0) + 120) && (bullet_y.at(0) <= monster_y.at(0) ) && (bullet_y.at(0) >= (monster_y.at(0) - 68)))
                {
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                if((doo_y+80 <= monster_y.at(0)) && (doo_y+80 >= monster_y.at(0) - 38) && (doo_x + 80 >= monster_x.at(0) ) && (doo_x <= (monster_x.at(0) + 120)) && (speed > 0) && (speed <= 25.298))
                {
                    HP--;
                    monster_y.erase(monster_y.begin());
                    monster_y.push_back(1500);
                }
                painter.drawImage(monster_x.at(0), monster_y.at(0)-68, monster4);
                break;
            default:
                break;
            }
        }

        if((keyA == true)||(keyD == true)||(keyW == true))
        {
            bullet_x.erase(bullet_x.begin());            
            bullet_x.push_back(doo_x + 40);
            bullet_y.erase(bullet_y.begin());
            bullet_y.push_back(doo_y + 28);
            if(keyA == true)
            {
                printA = true;
                printW = false;
                printD = false;
            }
            if(keyW == true)
            {
                printA = false;
                printW = true;
                printD = false;
            }
            if(keyD == true)
            {
                printA = false;
                printW = false;
                printD = true;
            }
        }
        if(printA == true)
        {
            b = bullet_x.at(0);
            b -= 18;
            bullet_x.erase(bullet_x.begin());
            bullet_x.push_back(b);
            painter.drawImage(bullet_x.at(0), bullet_y.at(0), bullet); 
        }
        else if(printD == true)
        {
            b = bullet_x.at(0);
            b += 18;
            bullet_x.erase(bullet_x.begin());
            bullet_x.push_back(b);
            painter.drawImage(bullet_x.at(0), bullet_y.at(0), bullet);
        }
        else if(printW == true)
        {
            b = bullet_y.at(0);
            b -= 20;
            bullet_y.erase(bullet_y.begin());
            bullet_y.push_back(b);
            painter.drawImage(bullet_x.at(0), bullet_y.at(0), bullet);
        }

        painter.drawImage(doo_x, doo_y, doodle);

        if(keyleft == true)
        {
            doodle.load("./dataset/images/doodleL.png");
        }
        if(keyright == true)
        {
            doodle.load("./dataset/images/doodleR.png");
        }
        font.setPointSize(20);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(20, 30, QString("Score: %1").arg(score));
        switch(HP)
        {
            case 1:
                painter.drawImage(400, 20, heart);
                break;  
            case 2:
                painter.drawImage(450, 20, heart);
                painter.drawImage(400, 20, heart);
                break;
            case 3:
                painter.drawImage(480, 20, heart);
                painter.drawImage(430, 20, heart);
                painter.drawImage(380, 20, heart);
                break;
            default:
                break;
        }
        if((doo_y >= 960)||(HP <= 0))
        {
            end = true;
            start = false;
            gamestart = false;
        }

    }
    if(end == true)
    {
        QPainter painter(this);
        QFont font;
        QPen pen;
        font.setPointSize(30);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(225, 300, tr("END"));
        painter.drawText(120, 400, tr("Press r To Menu"));
    }
 

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    
    
    if(event->timerId()==timerID && timerID!=0)
    {
        time +=1;
        update();
    }

    if(keyleft == true)
    {
        doo_x -= 10;
        if(doo_x < -40)
        {
            doo_x = 500;
        }
    }

    if(keyright == true)
    {
        doo_x += 10;
        if(doo_x > 500)
        {
            doo_x = -40;
        }
    }
}