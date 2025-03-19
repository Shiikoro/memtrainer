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

bool DatabaseManager::openDB(QString dbPath)
{
    if(db.isOpen())
        db.close();

    db.setDatabaseName(dbPath);

    if(!db.open())
        return false;

    return true;
}

void DatabaseManager::clodeDB()
{
    if(db.isOpen())
        db.close();
}

bool DatabaseManager::createDB(QList<int> colorNumberList, QString dbName)
{
    QString dbPath = QString("%1")
                            .arg(dbName);

    if(QFile::exists(dbPath))
        QFile::remove(dbPath);

    if(!openDB(dbPath))
        return false;
    if(!createTable())
        return false;

    for(int i = 0; i < colorNumberList.count(); i++)
    {
        if(!insertDatas(colorNumberList[i]))
            return false;
    }

    return true;
}

QList<int> DatabaseManager::getSequenzeDatas()
{
    QList<int> colorIndexList;
    QString queryString("SELECT * FROM sequence;");
    QSqlQuery query;

    if(query.exec(queryString))
        while(query.next()){
            int i = query.value(1).toInt();
            colorIndexList << i;
        }

    return colorIndexList;
}
