#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "databasemanager.h"
#include <QMainWindow>

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
    QTimer* timer;

    QList<int> getRandomNumberList();
    int getRandomNumber();
    void setdbDatas();
    void updateStatus();
    void checkClickedIndex();

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

inline void MainWindow::checkClickedIndex()
{

}
#endif // MAINWINDOW_H
