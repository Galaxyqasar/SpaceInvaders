#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QRect>
#include <QAction>
#include <QShortcut>
#include <QTimer>
#include "ui_main.h"
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupTimers();

public slots:
    void moveleft(int i = 5);
    void moverigth(int i = 5);
    void shootf();
    void projectile();
    void render();
    void check(int i);
    void spawnenemy();
    void enemy();
    void loosed();
    void togglepause();
    void blinklost();

Q_SIGNALS:
    void moved(int i);
    void hit();

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    bool paused;
    int score = 0;
    QPoint previous;
    QString scorestring;
    QPixmap displayOut;
    QImage display;
    QRect player, shootButton;
    QShortcut *moveLeft, *moveRigth, *shoot, *pause;
    QTimer *renderTimer, *projectileTimer, *enemyTimer, *losttimer;
    QList<QRect> enemys, projectiles;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
