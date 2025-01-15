#ifndef REPORTQUERY_H
#define REPORTQUERY_H

#include "../includes.h"

class ReportQuery : public QSqlQueryModel
{
    Q_OBJECT
private:
    QString* current_query;

public:
    ReportQuery(QString);
    ~ReportQuery();
};

#endif // REPORTQUERY_H
