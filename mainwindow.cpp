#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    db(new DatabaseManager),
    random(new QRandomGenerator(QRandomGenerator::securelySeeded())),
    interval(1000),
    buttonIndex(0),
    clickedIndex(0),
    timer(new QTimer()),
    actionGroup(new QActionGroup(this))
{
    setupUi(this);

    toolButtonList.append(btnRed);
    toolButtonList.append(btnGreen);
    toolButtonList.append(btnBlue);
    toolButtonList.append(btnYellow);

    connect(btnRed, SIGNAL(clicked()), this, SLOT(onRedclicked()));
    connect(btnGreen, SIGNAL(clicked()), this, SLOT(onGreenclicked()));
    connect(btnBlue, SIGNAL(clicked()), this, SLOT(onBlueclicked()));
    connect(btnYellow, SIGNAL(clicked()), this, SLOT(onYellowclicked()));

    setStyleSheet( QString( "QToolButton { border: none; }\n"
                            "QToolButton#btnRed { background: #200000; }\n"
                            "QToolButton#btnRed:checked, QToolButton#btnRed:pressed { background: #FF0000; }\n"
                            "QToolButton#btnYellow { background: #202000; }\n"
                            "QToolButton#btnYellow:checked, QToolButton#btnYellow:pressed { background: #FFFF00; }\n"
                            "QToolButton#btnGreen { background: #002000; }\n"
                            "QToolButton#btnGreen:checked, QToolButton#btnGreen:pressed { background: #00FF00; }\n"
                            "QToolButton#btnBlue { background: #000020; }\n"
                            "QToolButton#btnBlue:checked, QToolButton#btnBlue:pressed { background: #0000FF; }" ) );

    creatActions();
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
    return random->bounded(0,4);
}

void MainWindow::setdbDatas()
{
    dbDatas = db->getSequenzeDatas();
}

void MainWindow::updateStatus(int progress)
{
    lcdProgress->display(progress);
    progressBar->setValue(progress);
}

void MainWindow::creatAction(QString name)
{
    QAction* action = new QAction(name, actionGroup);
    action->setCheckable(true);
    menuMode->addAction(action);
}

void MainWindow::creatActions()
{
    for(int i = 0; i < modes.count(); i++)
    {
        creatAction(modes[i]);
    }
}

void MainWindow::checkClickedIndex(int i)
{
    if(dbDatas.isEmpty())
        return;

    if(dbDatas.count() == clickedIndex+1)
    {
        updateStatus(clickedIndex+1);
        hasPlayerWon(true);
        clickedIndex = 0;
        return;
    }
    if(i == dbDatas[clickedIndex])
        clickedIndex++;
    else
    {
        clickedIndex = 0;
        hasPlayerWon(false);
    }
    updateStatus(clickedIndex);
}

bool MainWindow::isTrainingModeActive()
{
    QList<QAction *> actionList = actionGroup->actions();
    for(int i = 0; i < actionList.count(); i++)
    {
        if(actionList[i]->isChecked() && actionList[i]->text() == modes[1])
            return true;
    }

    return false;
}

void MainWindow::hasPlayerWon(bool win)
{
    QString result = win == true? WIN_TEXT : LOSE_TEXT;

    QMessageBox::information(this, "Ergebniss", result);
}

void MainWindow::selectButtonPress()
{
    for(int i = 0; i < toolButtonList.count(); i++)
    {
        toolButtonList[i]->setDown(false);
    }

    if(buttonIndex >= dbDatas.count())
    {
        buttonIndex = 0;
        return;
    }

    toolButtonList[dbDatas[buttonIndex]]->setDown(true);
    buttonIndex++;
    updateStatus(buttonIndex);
    timer->singleShot(interval / 2, this, SLOT(buttonRelease()));
}

void MainWindow::buttonRelease()
{
    for(int i = 0; i < toolButtonList.count(); i++)
    {
        toolButtonList[i]->setDown(false);
    }

    timer->singleShot(interval / 2, this, SLOT(selectButtonPress()));
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
    QString dbName = QFileDialog::getSaveFileName(this, "Create new file", "", "");
    QList<int> randomNumberList = getRandomNumberList();
    db->createDB(randomNumberList, dbName);
}


void MainWindow::on_actionLoad_sequence_triggered()
{
    QString dbName = QFileDialog::getOpenFileName(this, "Select database file", "", "");
    db->openDB(dbName);
}


void MainWindow::on_actionStart_triggered()
{
    if(isTrainingModeActive())
        return;

    setdbDatas();
    if(timer->isActive() || buttonIndex > 0)
        return;
    clickedIndex = 0;
    selectButtonPress();
    progressBar->setRange(0, dbDatas.count());
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
    if(isTrainingModeActive())
        checkClickedIndex(0);
}

void MainWindow::onBlueclicked()
{
    if(isTrainingModeActive())
        checkClickedIndex(2);
}

void MainWindow::onYellowclicked()
{
    if(isTrainingModeActive())
        checkClickedIndex(3);
}

void MainWindow::onGreenclicked()
{
    if(isTrainingModeActive())
        checkClickedIndex(1);
}
