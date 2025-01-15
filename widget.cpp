#include "widget.h"

Widget::Widget
(
    // QString _db_source,
    QMap<EMITS_BTN_SIGNALS, QString>* _p_btn_tablename_links,
    QString& _report_query1, // query for report1
    QString& _report_query2, // query for report2
    QWidget *parent
)
:   QWidget(parent),
    p_btn_tablename_links{_p_btn_tablename_links}
{
    // setup this
    this->setAutoFillBackground(true);
    this->p_backColor = new QPalette;
    this->p_backColor->setColor(this->backgroundRole(), Qt::white);
    this->setPalette(*(this->p_backColor));

    this->resize(1000, 1100);

    // setup menues
        // setup left menu
    int menu_wdth = 80;
    int menu_hght = 650;
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
        this->p_tableSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG0, ""); // customers
        this->p_tableSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG1, ""); // products
        this->p_tableSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG2, ""); // oreders
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
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG3, ""); // call report1
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG4, ""); // call report2
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
}

Widget::~Widget()
{
    delete this->p_btn_tablename_links;
    delete this->p_report1;
    delete this->p_report2;
}
