#ifndef DEFINITIONSQSQLQUERYMODEL_H
#define DEFINITIONSQSQLQUERYMODEL_H

#include <QtSql/QSqlQueryModel>

class DefinitionsQSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit DefinitionsQSqlQueryModel(QObject *parent = 0);

    QVariant data(const QModelIndex &item, int role) const;
};

#endif // DEFINITIONSQSQLQUERYMODEL_H
