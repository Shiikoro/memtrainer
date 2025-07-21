#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "databasemanager.h"
#include <QMainWindow>

#define WIN_TEXT QString("Du hast es geschafft!")
#define LOSE_TEXT QString("Versuch es noch einmal.")

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

private:
    int newAmmount;
    DatabaseManager* db;
    QRandomGenerator* random;
    QList<int> dbDatas;
    QList<QToolButton*> toolButtonList;
    int interval;
    int buttonIndex;
    int clickedIndex;
    QTimer* timer;
    QActionGroup* actionGroup;
    QList<QString> modes = *new QList<QString> << "Player" << "Training";

    QList<int> getRandomNumberList();
    int getRandomNumber();
    void setdbDatas();
    void updateStatus(int progress);
    void creatAction(QString name);
    void creatActions();
    void checkClickedIndex(int i);
    bool isTrainingModeActive();
    void hasPlayerWon(bool win);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectButtonPress();
    void buttonRelease();
    void on_actionCreate_new_File_triggered();
    void on_actionSave_sequence_as_triggered();
    void on_actionLoad_sequence_triggered();
    void on_actionStart_triggered();
    void on_actionInterval_triggered();
    void onRedclicked();
    void onBlueclicked();
    void onYellowclicked();
    void onGreenclicked();
};
#endif // MAINWINDOW_H
