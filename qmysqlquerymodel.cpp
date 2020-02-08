#include "qmysqlquerymodel.h"

QMySqlQueryModel::QMySqlQueryModel(QObject *parent):
    QSqlQueryModel(parent)
{
    QString sql="select "
                "userNumId ,"
                "TaskNum "
                "from taskinfo where executor =''";
    this->setQuery(sql);
    this->setHeaderData(0,Qt::Horizontal,"发布ID");//设置表头显示的数据
    this->setHeaderData(1,Qt::Horizontal,"订单编号");
}

QVariant QMySqlQueryModel::data(const QModelIndex &item, int role) const
{
    if (role == Qt::TextAlignmentRole)//默认代理的对齐方式
    {
        QVariant value = (Qt::AlignCenter);
        return value;
    }
    else
        return QSqlQueryModel::data(item,role);
}
