#include "widget.h"

Widget::Widget
(
    // QString _db_source,
    QMap<EMITS_BTN_SIGNALS, QString>* _p_btn_tablename_links,
    QMap<EMITS_BTN_SIGNALS, QString>* _p_btn_report_links,
    QWidget *parent
)
:   QWidget(parent),
    p_btn_tablename_links(_p_btn_tablename_links),
    p_btn_report_links(_p_btn_report_links)
{
    // setup this
    this->setAutoFillBackground(true);
    this->p_backColor = new QPalette;
    this->p_backColor->setColor(this->backgroundRole(), Qt::white);
    this->setPalette(*(this->p_backColor));

    this->resize(1000, 800);

    // setup menues
        // setup left menu
    int menu_wdth = 80;
    int menu_hght = 250;
    int menu_pos_x = 10;
    int menu_pos_y = 20;

    this->p_tableSwapMenu = new MenuBar
    (
        new QSize(menu_wdth, menu_hght),
        new QSize(menu_pos_x, menu_pos_y),
        true,
        this
    );
    {
        this->p_tableSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG0, ":/ico/customers.png"); // customers
        this->p_tableSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG1, ":/ico/orders.png"); // products
        this->p_tableSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG2, ":/ico/products.png"); // oreders
    }
    this->p_tableSwapMenu->show();

        // setup right menu
    this->p_reportSwapMenu = new MenuBar
    (
        new QSize(menu_wdth, menu_hght),
        new QSize(this->width()-menu_pos_x, menu_pos_y),
        true,
        this
    );
    {
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG3, ":/ico/reports.png"); // call report1
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG4, ":/ico/reports.png"); // call report2
    }
    this->p_reportSwapMenu->show();

    // setup top bar
        /*
        int topbar_wdth = this->width()-
                this->p_tableSwapMenu->size().width() -
                          this->p_reportSwapMenu->size().width();
        */
    int topbar_wdth = this->width()-2*menu_wdth;
    int topbar_hght = 60;
    this->p_topBar = new TopBar
    (
        new QSize(
            // this->p_tableSwapMenu->size().width(),
            // this->p_tableSwapMenu->pos().y()
            menu_wdth,
            menu_pos_y
        ),
        new QSize(
            topbar_wdth,
            topbar_hght
        ),
        this
    );
    this->p_topBar->show();

    // setup table view area
    this->p_current_model = new QTableView;
    this->p_current_model->setGeometry
    (
        menu_wdth,
        menu_pos_y,
        topbar_wdth,
        this->height()
    );

    connect // table swap
    (
        this->p_tableSwapMenu,
        &MenuBar::sig_transmission,
        this,
        &Widget::slot_table_swapper
    );

    connect // table swap
    (
        this->p_reportSwapMenu,
        &MenuBar::sig_transmission,
        this,
        &Widget::slot_show_report
    );
}

Widget::~Widget()
{
    delete this->p_btn_tablename_links;
    delete this->p_btn_report_links;
}

void Widget::slot_table_swapper(EMITS_BTN_SIGNALS _sig)
{
    QSqlTableModel* model = new QSqlTableModel;
    QString table_name =
        this->p_btn_tablename_links->lowerBound(_sig).value();

    model->setTable
    (
        table_name
    );
    model->select(); // load data

    this->p_current_model->setModel(model);

    emit this->sig_showed_table(table_name);
}

void Widget::slot_show_report(EMITS_BTN_SIGNALS _sig)
{
    QSqlQueryModel* query_model = new QSqlQueryModel;
    QString report_name =
        this->p_btn_report_links->lowerBound(_sig).value();
    query_model->setQuery
    (
        report_name
    );

    this->p_current_model->setModel(query_model);

    emit this->sig_showed_report(report_name);
}

void Widget::slot_add_filed(void)
{

}

void Widget::slot_delete_field(void)
{

}
