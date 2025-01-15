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

    // setup left menu
    this->p_tableSwapMenu = new MenuBar
    (
        new QSize(80, 650),
        new QSize(10, 20),
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
        new QSize(80, 650),
        new QSize(this->width()-10, 20),
        true,
        this
    );
    {
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG3, ""); // call report1
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG4, ""); // call report2
    }
    this->p_reportSwapMenu->show();

    // setup top bar

}

Widget::~Widget()
{
    delete this->p_btn_tablename_links;
    delete this->p_report1;
    delete this->p_report2;
}
