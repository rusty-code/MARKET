#include "ReportQuery.h"


ReportQuery::ReportQuery(QString _report_query)
{
    this->current_query = new QString(_report_query);
    this->setQuery(_report_query);
}

ReportQuery::~ReportQuery()
{
    delete this->current_query;
}
