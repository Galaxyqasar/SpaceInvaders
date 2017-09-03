#include "ui_main.h"

UiMain::UiMain()
{

}

void UiMain::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QStringLiteral("Taschenrechner"));
    MainWindow->setGeometry(50, 50, 540, 540);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    //setup Widgets
    mainDisplay = new QLabel(centralWidget);
    mainDisplay->setStyleSheet("border: 20px solid grey");
    MainWindow->setCentralWidget(centralWidget);
    scorelabel = new QLabel(mainDisplay);
    scorelabel->setStyleSheet("border: 0px solid gray");
    scorelabel->setGeometry(QRect(0, 0, 540, 20));
    lostlabel= new QLabel(mainDisplay);
    lostlabel->setGeometry(QRect(0, 180, 540, 180));
    lostlabel->setStyleSheet("border: 0px solid red");
    lostlabel->setText("Lost");
    QFont font;
    font.setBold(true);
    font.setPointSize(100);
    lostlabel->setFont(font);
    lostlabel->setAlignment(Qt::AlignCenter);
    lostlabel->hide();
    retranslateUi(MainWindow);
}

void UiMain::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
}


