#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QRect>
#include <QAction>
#include <QShortcut>
#include <QTimer>
#include "ui_main.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupTimers();

public slots:
    void moveleft();
    void moverigth();
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
    bool paused;
    int score = 0;
    QString scorestring;
    QPixmap displayOut;
    QImage display;
    QRect player;
    QShortcut *moveLeft, *moveRigth, *shoot, *pause;
    QTimer *renderTimer, *projectileTimer, *enemyTimer, *losttimer;
    QList<QRect> enemys, projectiles;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
