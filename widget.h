#ifndef WIDGET_H
#define WIDGET_H

#include "includes.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    QTableView* current_model;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    /*
     * Get name of current table view
    */
    void slot_add_filed(void);
    void slot_delete_field(void);

    /*
     * swap current table name at TopBar
     * swap model at this->QTableView
    */
    void slot_table_swapper(EMITS_BTN_SIGNALS);
    void slot_show_report(EMITS_BTN_SIGNALS);

signals:
    void sig_showed_table(QString& /*table name*/);
    void sig_showed_report(QString& /*table name*/);
};
#endif // WIDGET_H
