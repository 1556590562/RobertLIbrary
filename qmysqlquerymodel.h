#ifndef QMYSQLQUERYMODEL_H
#define QMYSQLQUERYMODEL_H

#include<QtSql/QSqlQueryModel>

class QMySqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    QMySqlQueryModel();

public:
    explicit QMySqlQueryModel(QObject *parent=0);
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
};

#endif // QMYSQLQUERYMODEL_H
