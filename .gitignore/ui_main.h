#ifndef UI_Main_HH
#define UI_Main_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>


class UiMain {

public:
    UiMain();
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    //
    QWidget *centralWidget;
    QLabel *mainDisplay, *lostlabel, *scorelabel;
    //Add your Widgets

};

namespace Ui {
    class MainWindow: public UiMain {};
}



#endif // UI_TASCHENRECHNER_H
