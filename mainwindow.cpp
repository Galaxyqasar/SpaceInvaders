#include "mainwindow.h"
#include <time.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTimers();
    srand((unsigned)time(NULL));
    displayOut = QPixmap(500, 500);
    display = QImage(500, 500, QImage::Format_ARGB32);
    moveLeft = new QShortcut(this);
    moveRigth = new QShortcut(this);
    shoot = new QShortcut(this);
    pause = new QShortcut(this);
    moveLeft->setKey(QKeySequence(Qt::Key_Left));
    moveRigth->setKey(QKeySequence(Qt::Key_Right));
    shoot->setKey(QKeySequence(Qt::Key_Space));
    pause->setKey(QKeySequence(Qt::Key_P));
    connect(moveRigth, SIGNAL(activated()), this, SLOT(moverigth()));
    connect(moveLeft, SIGNAL(activated()), this, SLOT(moveleft()));
    connect(shoot, SIGNAL(activated()), this, SLOT(shootf()));
    connect(pause, SIGNAL(activated()), this, SLOT(togglepause()));
    connect(this, SIGNAL(moved(int)), this, SLOT(check(int)));
    connect(this, SIGNAL(hit()), this, SLOT(loosed()));
    display.fill(Qt::white);
    player.setRect(240, 480, 20, 20);
    for(int x=player.x();x<player.x()+player.width();x++){
        for(int y=player.y();y<player.y()+player.height();y++)
            display.setPixel(x,y,QColor(Qt::black).rgb());
    }
    ui->mainDisplay->setPixmap(QPixmap::fromImage(display));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupTimers()
{
    renderTimer = new QTimer(this);
    renderTimer->setInterval(15);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(render()));
    renderTimer->start(15);

    projectileTimer = new QTimer(this);
    projectileTimer->setInterval(30);
    connect(projectileTimer, SIGNAL(timeout()), this, SLOT(projectile()));
    projectileTimer->start(30);

    enemyTimer = new QTimer(this);
    enemyTimer->setInterval(3000);
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnenemy()));
    enemyTimer->start(3000);

    losttimer = new QTimer(this);
    losttimer->setInterval(1000);
    connect(losttimer, SIGNAL(timeout()), this, SLOT(blinklost()));

    connect(projectileTimer, SIGNAL(timeout()), this, SLOT(enemy()));
}

void MainWindow::render()
{
    display.fill(QColor(Qt::darkGray).darker(200));
    //player
    for(int x=player.x();x<player.x()+player.width();x++){
        for(int y=player.y();y<player.y()+player.height();y++)
            display.setPixel(x,y,QColor(Qt::black).rgb());
    }
    qDebug() <<"Player"<<player.x()<<player;
    //enemys
    for(int i = 0;i<enemys.size();i++){
        for(int x=0;x<enemys.at(i).width();x++){
            for(int y=0;y<enemys.at(i).height();y++)
                display.setPixel(x+enemys.at(i).x(),\
                                 y+enemys.at(i).y(),\
                                 QColor(Qt::red).rgb());
        }
        qDebug() <<"enemys;"<<i<<";"<<enemys.at(i);
    }
    //projectiles
    for(int i = 0;i<projectiles.size();i++){
        for(int x=0;x<projectiles.at(i).width();x++){
            for(int y=0;y<projectiles.at(i).height();y++)
                display.setPixel(x+projectiles.at(i).x()-projectiles.at(i).width()/2,\
                                 y+projectiles.at(i).y(),\
                                 QColor(Qt::blue).rgb());
        }
        qDebug() <<"projectiles;"<<i<<";"<<projectiles.at(i);
    }
    ui->mainDisplay->setPixmap(QPixmap::fromImage(display));
    ui->scorelabel->setText("Score:"+scorestring);
    qDebug() <<ui->scorelabel->text();
}

void MainWindow::check(int i)
{
    //check for enemys hit
    QRect tmp;
    for(int j=0;j<enemys.size();j++){
        if(enemys.at(j).intersects(projectiles.at(i))){
            enemys.removeAt(j);
            projectiles.replace(i, tmp);
            if(enemyTimer->interval()>500)
                enemyTimer->setInterval(enemyTimer->interval()-100);
            score++;
            scorestring.setNum(score);
            qDebug()<<"Timer:"<<enemyTimer->interval();
        }
    }
}

void MainWindow::spawnenemy()
{
    int position = (rand()%480+0);
    enemys.append(QRect(position, 20, 20, 20));
    qDebug() <<"Spawn"<<position;
}

void MainWindow::enemy()
{
    if(!enemys.isEmpty()){
        QRect tmp;
        for(int i=0;i<enemys.size();i++){
            if(enemys.at(i).y() >=480){
                enemys.removeAt(i);
                emit hit();
            }
            else{
                tmp.setY(enemys.at(i).y()+1);
                tmp.setX(enemys.at(i).x());
                tmp.setWidth(enemys.at(i).width());
                tmp.setHeight(enemys.at(i).height());
                if(tmp.intersects(player))
                    enemys.removeAt(i);
                else
                    enemys.replace(i, tmp);
            }
        }
    }
}

void MainWindow::loosed()
{
    projectileTimer->stop();
    enemyTimer->stop();
    renderTimer->stop();
    ui->lostlabel->show();
    losttimer->start();
}

void MainWindow::togglepause()
{
    if(paused){
        projectileTimer->start();
        enemyTimer->start();
        renderTimer->start();
        paused = false;
    }
    else{
        projectileTimer->stop();
        enemyTimer->stop();
        renderTimer->stop();
        paused = true;
    }
}

void MainWindow::blinklost()
{
    if(ui->lostlabel->isVisible())
        ui->lostlabel->hide();
    else
        ui->lostlabel->show();
}

void MainWindow::moveleft()
{
    if(player.x()>=5)
        player.setRect(player.x()-5, player.y(), player.width(), player.height());
}

void MainWindow::moverigth()
{
    if(player.x()<=475)
        player.setRect(player.x()+5, player.y(), player.width(), player.height());
}

void MainWindow::shootf()
{
    projectiles.append(QRect(player.x()+player.width()/2, player.y(), player.width()/2, player.height()/2));
    qDebug() <<"Fire"<<projectiles.size();
}

void MainWindow::projectile()
{
    if(!projectiles.isEmpty()){
        QRect tmp;
        for(int i=0;i<projectiles.size();i++){
            if(projectiles.at(i).y() <=0)
                projectiles.removeAt(i);
            else{
                tmp.setY(projectiles.at(i).y()-3);
                tmp.setX(projectiles.at(i).x());
                tmp.setWidth(projectiles.at(i).width());
                tmp.setHeight(projectiles.at(i).height());
                projectiles.replace(i, tmp);
                emit moved(i);
            }
        }
    }
}
