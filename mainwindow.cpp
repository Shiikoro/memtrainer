#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    db(new DatabaseManager),
    random(new QRandomGenerator()),
    interval(1000)
{
    setupUi(this);

    toolButtonList.append(btnRed);
    toolButtonList.append(btnGreen);
    toolButtonList.append(btnBlue);
    toolButtonList.append(btnYellow);

    connect(btnRed, SIGNAL(clicked()), this, SLOT(onRedclicked()));

    setStyleSheet( QString( "QToolButton { border: none; }\n"
                            "QToolButton#btnRed { background: #200000; }\n"
                            "QToolButton#btnRed:checked, QToolButton#btnRed:pressed { background: #FF0000; }\n"
                            "QToolButton#btnYellow { background: #202000; }\n"
                            "QToolButton#btnYellow:checked, QToolButton#btnYellow:pressed { background: #FFFF00; }\n"
                            "QToolButton#btnGreen { background: #002000; }\n"
                            "QToolButton#btnGreen:checked, QToolButton#btnGreen:pressed { background: #00FF00; }\n"
                            "QToolButton#btnBlue { background: #000020; }\n"
                            "QToolButton#btnBlue:checked, QToolButton#btnBlue:pressed { background: #0000FF; }" ) );
}

MainWindow::~MainWindow()
{
    if(db) delete db;
    if(random) delete random;
}

QList<int> MainWindow::getRandomNumberList()
{
    QList<int> listInt;

    while(listInt.count() < newAmmount)
    {
        listInt << getRandomNumber();
    }

    return listInt;
}

int MainWindow::getRandomNumber()
{
    return random->bounded(1,4);
}

void MainWindow::selectButtonPress()
{
    if(dbDatas.isEmpty())
        return;

    toolButtonList[dbDatas.takeFirst()]->click(); //Buttons sind die richtigen dennoch wird click nicht regestriert.

    QTimer::singleShot(interval, this, SLOT(selectButtonPress()));
}

void MainWindow::on_actionCreate_new_File_triggered()
{
    bool ok;
    int ammount = QInputDialog::getInt(this, "Ammount", "Ammount: ", 8, 1, 128, 1, &ok);
    if(ok)
        newAmmount = ammount;
}


void MainWindow::on_actionSave_sequence_as_triggered()
{
    QString test = QFileDialog::getSaveFileName(this, "Create new file", "", "");
    QList<int> randomNumberList = getRandomNumberList();
    db->createDB(randomNumberList, test);
}


void MainWindow::on_actionLoad_sequence_triggered()
{
    QString test = QFileDialog::getOpenFileName(this, "Select database file", "", "");
    db->openDB(test);
}


void MainWindow::on_actionStart_triggered()
{
    dbDatas = db->getSequenzeDatas();
    selectButtonPress();
}


void MainWindow::on_actionInterval_triggered()
{
    bool ok;
    int ammount = QInputDialog::getInt(this, "Interval", "Interval in milliseconds: ", 1000, 0, 10000, 1, &ok);
    if(ok)
        interval = ammount;
}

void MainWindow::onRedclicked()
{
    qWarning() << "RED";
}

