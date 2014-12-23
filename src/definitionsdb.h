#ifndef DEFINITIONSDB_H
#define DEFINITIONSDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>
#include <QtCore/QDir>

QSqlError connectDefinitionsDb(QDir userDir)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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
    QSqlQuery* qry = new QSqlQuery();

    QSqlQueryModel* nationModel = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    nationModel->setQuery(*qry);
    return nationModel;
}

#endif // DEFINITIONSDB_H
