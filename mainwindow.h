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
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionCreate_new_File_triggered();
};
#endif // MAINWINDOW_H
