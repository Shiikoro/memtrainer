#include "databasemanager.h"

DatabaseManager::DatabaseManager() :
    db(QSqlDatabase::addDatabase("QSQLITE"))
{
}

bool DatabaseManager::createTable()
{
    QString queryString("CREATE TABLE sequence"
                          "("
                          "id integer primary key,"
                          "colorIndex integer not null"
                          ");");
    QSqlQuery query;
    return query.exec(queryString);
}

bool DatabaseManager::insertDatas(int colorNumber)
{
    QString queryString = QString("INSERT INTO sequence (colorIndex) VALUES (%1)")
                              .arg(colorNumber);
    QSqlQuery query;
    return query.exec(queryString);
}

bool DatabaseManager::openDB(QString dbName)
{
    QString dbPath = QString("%1/%2")
        .arg(QApplication::applicationDirPath())
        .arg(dbName);

    db.setDatabaseName(dbName);

    if(!db.open())
        return false;

    return true;
}

bool DatabaseManager::createDB(QList<int> colorNumberList, QString dbName)
{
    QString dbPath = QString("%1/%2")
        .arg(QApplication::applicationDirPath())
        .arg(dbName);

    if(QFile::exists(dbPath))
        QFile::remove(dbPath);

    if(!openDB(dbPath))
        return false;
    qWarning() << "Open";
    if(!createTable())
        return false;
    qWarning() << "Tables";

    for(int i = 0; i < colorNumberList.count(); i++)
    {
        if(!insertDatas(colorNumberList[i]))
            return false;
    }

    return true;
}
