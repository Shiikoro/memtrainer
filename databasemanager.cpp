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
    bool b = query.exec(queryString);
    qWarning() << query.lastError();
    return b;
}

bool DatabaseManager::insertDatas(int colorNumber)
{
    qWarning() << colorNumber;
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
    if(db.isOpen())
        db.close();

    QString dbPath = QString("%1")
                            .arg(dbName);

    if(QFile::exists(dbPath))
        QFile::remove(dbPath);

    if(!openDB(dbPath))
        return false;
    qWarning() << "All fine";

    if(!createTable())
        return false;

    qWarning() << "All fine";
    for(int i = 0; i < colorNumberList.count(); i++)
    {
        if(!insertDatas(colorNumberList[i]))
            return false;
    }

    qWarning() << "All fine";

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
