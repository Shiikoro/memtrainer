#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QList<int> list;
    list << 1 << 2;
    DatabaseManager* db = new DatabaseManager();
    qWarning() << db->createDB(list, "test.seq");
    setupUi(this);

}

MainWindow::~MainWindow() {}

void MainWindow::on_actionCreate_new_File_triggered()
{
    bool ok;
    int ammount = QInputDialog::getInt(this, "Ammount", "Ammount: ", 8, 1, 128, 1, &ok);
    if(ok)
        newAmmount = ammount;
}

