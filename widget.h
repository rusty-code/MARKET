#ifndef WIDGET_H
#define WIDGET_H

#include "includes.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel* current_model;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void slot_add_filed(void);
    void slot_delete_field(void);

signals:

};
#endif // WIDGET_H
