#include "widget.h"

#include <QApplication>



void test()
{
    QString report1 =   "SELECT p.ProductName, od.SummaryCount "\
        "FROM order_details od "\
        "JOIN products p ON od.ProductId = p.Id "\
        "JOIN orders o ON od.OrderId = o.Id "\
        "WHERE o.ClientEmail = 'email1@mail';";
    qDebug() << report1;
}

int main(int argc, char *argv[])
{
    QApplication app_master(argc, argv);

    // connect to db here
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName(QCoreApplication::applicationDirPath() + "/ikmdb.db");
    db.setDatabaseName("/home/pwr/WORKSPACE/qt_workspace/MARKET/OtherFiles/ikmdb.db");
    if(!db.open())
        qDebug() << "Bad db open!";
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
        QString report1 = "SELECT p.ProductName, od.SummaryCount FROM order_details od "
                          "JOIN products p ON od.ProductId = p.Id JOIN orders o "
                          "ON od.OrderId = o.Id WHERE o.ClientEmail = 'email1@mail';";
        p_links_btn_reports->insert(EMITS_BTN_SIGNALS::SIG0, report1);

        report1 = "SELECT c.Name, c.SecondName, c.Email FROM order_details od "
                  "JOIN orders o ON od.OrderId = o.Id JOIN customers c "
                  "ON o.ClientEmail = c.Email JOIN products p "
                  "ON od.ProductId = p.Id WHERE p.ProductName = 'Milk';";
        p_links_btn_reports->insert(EMITS_BTN_SIGNALS::SIG1, report1);
    }
    // ------------------


    Widget mainwnd
        (
            p_links_btn_tables,
            p_links_btn_reports
            );
    qDebug() << "main show";
    mainwnd.show();


    return app_master.exec();
}
