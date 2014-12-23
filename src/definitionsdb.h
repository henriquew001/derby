#ifndef DEFINITIONSDB_H
#define DEFINITIONSDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>
#include <QtCore/QDir>
#include "definitionsqsqlquerymodel.h"

QSqlError connectDefinitionsDb(QDir userDir)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");QString connection;
    // Need to change to install definitions dir
    db.setDatabaseName(userDir.absolutePath() + "/definitions.sqlite");

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

#endif // DEFINITIONSDB_H
