#ifndef WIDGET_H
#define WIDGET_H

#include "includes.h"
#include "menu_bar/MenuBar.h"
#include "menu_bar/TopBar.h"
#include "reports/ReportQuery.h"


class Widget : public QWidget
{
    Q_OBJECT

private:
    QTableView* p_current_model;
    QMap<EMITS_BTN_SIGNALS, QString>* p_btn_tablename_links;
    QMap<EMITS_BTN_SIGNALS, QString>* p_btn_report_links;
    // ReportQuery* p_report1;
    // ReportQuery* p_report2;

    MenuBar* p_tableSwapMenu; // left menu
    MenuBar* p_reportSwapMenu; // right menu
    TopBar* p_topBar; // top menu

    QPalette* p_backColor; // for fill backgounds of widgets

public:
    Widget
    (
        // QString,
        QMap<EMITS_BTN_SIGNALS, QString>*,
        QMap<EMITS_BTN_SIGNALS, QString>*,
        QWidget *parent = nullptr
    );
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
    void sig_showed_table(QString /*table name*/);
    void sig_showed_report(QString /*table name*/);
};
#endif // WIDGET_H
