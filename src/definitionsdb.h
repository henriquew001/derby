#ifndef DEFINITIONSDB_H
#define DEFINITIONSDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>
#include <QtCore/QDir>
#include "definitionsqsqlquerymodel.h"

QSqlError connectDefinitionsDb(QDir dbDir)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // Need to change to install definitions dir
    db.setDatabaseName(dbDir.absolutePath());

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if ((!tables.contains("Teams", Qt::CaseInsensitive)
         && tables.contains("Leagues", Qt::CaseInsensitive))) {
        QMessageBox msgBox;
        msgBox.setText("The definitions file is not correct.");
        msgBox.exec();
        return QSqlError();
    }

    return QSqlError();
}

QSqlQueryModel* getdDefinitionsList(const QString str)
{
    QSqlQueryModel* dbModel = new QSqlQueryModel();
    dbModel->setQuery(str);
    return dbModel;
}

QSqlError connectGameDb(QDir dbDir)
{
    if(QFile::exists(dbDir.absolutePath())) QFile::remove(dbDir.absolutePath());
    QSqlDatabase gameDB = QSqlDatabase::addDatabase("QSQLITE", "Game");
    // Need to change to install definitions dir
    gameDB.setDatabaseName(dbDir.absolutePath());

    if (!gameDB.open())
        return gameDB.lastError();

    QSqlQuery *q = new QSqlQuery("CREATE TABLE Gamester(id INTEGER PRIMARY KEY, GamesterName VARCHAR, GamesterTeam VARCHAR, StartLeague VARCHAR)", gameDB);
    q->exec();

    return QSqlError();
}
#endif // DEFINITIONSDB_H
