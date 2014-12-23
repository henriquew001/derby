#include "definitionsqsqlquerymodel.h"
#include <QPixmap>
#include <QIcon>
#include <QtSql/QSqlRecord>
#include <QDir>

DefinitionsQSqlQueryModel::DefinitionsQSqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

QVariant DefinitionsQSqlQueryModel::data(const QModelIndex &item, int role) const
{
    if (role == Qt::DecorationRole)
    {
        switch(item.column())
        {
        case 0: // column 0 contains text data
            QPixmap image;
            image.loadFromData(record(item.row()).value(1).toByteArray()); // column 1 contains BLOB data
            return QVariant(QIcon(image.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }
    }
    return QSqlQueryModel::data(item, role);
}
