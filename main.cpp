#include "widget.h"

#include <QApplication>

void setup()
{
    // connect to db here
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/ikmdb.db");
    // ------------------


    // create map links sig <-> table name here
    QMap<EMITS_BTN_SIGNALS, QString>* p_links_btn_tables =
        new QMap<EMITS_BTN_SIGNALS, QString>;
    {
        p_links_btn_tables->insert(EMITS_BTN_SIGNALS::SIG0, "customers");
        p_links_btn_tables->insert(EMITS_BTN_SIGNALS::SIG1, "orders");
        p_links_btn_tables->insert(EMITS_BTN_SIGNALS::SIG2, "products");
    }
    // ------------------

    // create qstrings query for reports here
    QMap<EMITS_BTN_SIGNALS, QString>* p_links_btn_reports =
        new QMap<EMITS_BTN_SIGNALS, QString>;
    {
        p_links_btn_tables->insert(EMITS_BTN_SIGNALS::SIG0, "");
        p_links_btn_tables->insert(EMITS_BTN_SIGNALS::SIG1, "");
    }
    // ------------------


    Widget mainwnd
    (
        p_links_btn_tables,
        p_links_btn_reports
    );
    mainwnd.show();

}

void test()
{
    QString str = "qr23rdd";
    qDebug() << str.toInt() << '\n';
    str = "";
    qDebug() << str.toInt() << '\n';
}

int main(int argc, char *argv[])
{
    QApplication app_master(argc, argv);

    setup();

    return app_master.exec();
}
