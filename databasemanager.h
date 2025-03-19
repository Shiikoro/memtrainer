#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtWidgets>
#include <QtSql>

class DatabaseManager
{
private:
    QSqlDatabase db;
    bool createTable();
    bool fillTable();
    bool insertDatas(int colorNumber);

public:
    DatabaseManager();
    bool openDB(QString dbPath);
    void clodeDB();
    bool createDB(QList<int> colorNumberList, QString dbName);
    QList<int> getSequenzeDatas();
};

#endif // DATABASEMANAGER_H
