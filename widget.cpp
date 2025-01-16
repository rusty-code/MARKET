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
    p_btn_report_links(_p_btn_report_links),
    current_table_name(" ")
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
        // new QSize(this->width()-menu_pos_x, menu_pos_y),
        new QSize(this->width()-menu_wdth, menu_pos_y),
        true,
        this
    );
    {
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG0, ":/ico/reports.png"); // call report1
        this->p_reportSwapMenu->appendObject(EMITS_BTN_SIGNALS::SIG1, ":/ico/reports.png"); // call report2
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
    this->p_current_model = new QTableView(this);
    this->setPalette(QPalette(Qt::white));
    this->p_current_model->setGeometry
    (
        menu_wdth,
        topbar_hght+20,
        topbar_wdth,
        this->height()-topbar_hght-20
    );
    this->p_current_model->show();

    connect // table swap
    (
        this->p_tableSwapMenu,
        &MenuBar::sig_transmission,
        this,
        &Widget::slot_table_swapper
    );

    connect // report swap
    (
        this->p_reportSwapMenu,
        &MenuBar::sig_transmission,
        this,
        &Widget::slot_show_report
    );

    connect( // add filed button
        this->p_topBar,
        &TopBar::sig_add_new_row,
        this,
        &Widget::slot_add_filed
        );

    connect(
        this->p_topBar,
        &TopBar::sig_delete_selected_row,
        this,
        &Widget::slot_delete_field
        );

    connect( // set table name
        this,
        &Widget::sig_showed_table,
        this->p_topBar,
        &TopBar::slot_set_tname
        );

    connect( // set report name
        this,
        &Widget::sig_showed_report,
        this->p_topBar,
        &TopBar::slot_set_tname
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
    this->current_table_name =
        this->p_btn_tablename_links->lowerBound(_sig).value();

    model->setTable
    (
        this->current_table_name
    );
    model->select(); // load data

    this->p_current_model->setModel(model);
    this->update();
    emit this->sig_showed_table(this->current_table_name);
}

void Widget::slot_show_report(EMITS_BTN_SIGNALS _sig)
{
    QSqlQueryModel* query_model = new QSqlQueryModel;
    QString report_name =
        this->p_btn_report_links->lowerBound(_sig).value();


    qDebug() << report_name;
    query_model->setQuery
    (
        report_name
    );

    if(query_model->lastError().isValid())
    {
        qDebug() << "query exec error";
    }

    this->p_current_model->setModel(query_model);
    this->current_table_name = "Report";

    emit this->sig_showed_report(this->current_table_name);
}

void Widget::slot_add_filed(void)
{
    if(this->current_table_name == " ")
        return;

    QList<QString>* p_lst = new QList<QString>;
    if(this->current_table_name == "customers")
    {
        p_lst->append("Email");
        p_lst->append("Name");
        p_lst->append("Second name");
    }
    else if(this->current_table_name == "products")
    {
        p_lst->append("Product name");
        p_lst->append("Price");
    }
    else if(this->current_table_name == "orders")
    {
        p_lst->append("OrderId");
        p_lst->append("Date");
        p_lst->append("Email");
        // ====
        p_lst->append("SummaryCount");
        p_lst->append("ProductId");
    }
    PushData* p_input_wnd = new PushData(p_lst, this->p_backColor);

    connect
    (
        p_input_wnd,
        &PushData::sig_approved_data,
        this,
        &Widget::slot_add_field_approved
        );
    connect
    (
        p_input_wnd,
        &PushData::sig_cancel,
        this,
        &Widget::slot_add_field_approved
        );
    p_input_wnd->show();
    // p_input_wnd->close();
}

void Widget::slot_add_field_approved
(
    QList<QString>* _data,
    PushData* _inpt_wnd
)
{
    if(_data == nullptr)
    {
        _inpt_wnd->close();
        return;
    }

    QSqlTableModel model;

    if(this->current_table_name == "customers")
    {
        model.setTable("customers");

        model.insertRows(0, 1);
        model.setData(model.index(0, 0), _data->at(0));
        model.setData(model.index(0, 1), _data->at(1));
        model.setData(model.index(0, 2), _data->at(2));
    }
    else if(this->current_table_name == "products")
    {
        model.setTable("products");

        model.insertRows(0, 1);
        model.setData(model.index(0, 0), _data->at(0));
        model.setData(model.index(0, 1), _data->at(1));
    }
    else if(this->current_table_name == "orders")
    {
        model.setTable("orders");

        model.insertRows(0, 1);
        model.setData(model.index(0, 0), _data->at(0));
        model.setData(model.index(0, 1), _data->at(1));
        model.setData(model.index(0, 2), _data->at(2));

        QSqlTableModel submodel;
        submodel.setTable("order_details");

        submodel.setData(submodel.index(0, 0), _data->at(0)); // may be not wor
        submodel.setData(submodel.index(0, 1), _data->at(3));
        submodel.setData(submodel.index(0, 4), _data->at(4));

        if(!submodel.submitAll())
            qDebug() << "Order_details submit error";
    }
    if(!model.submitAll())
        qDebug() << model.tableName() << " submit error";

    _inpt_wnd->close();
    this->p_current_model->update();
}

void Widget::slot_delete_field(void)
{
    // QSqlTableModel* tmp_model = new QSqlTableModel;
    // tmp_model->setTable(this->current_table_name);

    // QItemSelectionModel* mdl = new QItemSelectionModel;
    // mdl->setModel(this->p_current_model->se);

    // QModelIndexList indexes = mdl->selectedIndexes();
    QModelIndexList indexes = this->p_current_model->selectionModel()->selectedIndexes();
    for
    (
        auto row_ind = indexes.begin();
        row_ind != indexes.end();
        ++row_ind
    )
    {
        this->p_current_model->model()->removeRow(row_ind->row());
        // tmp_model->revertRow(row_ind->row());

    }
    // if(!this->p_current_model->model()->submit())
    // {
    //     qDebug() << "error remove rows";
    // }
    // this->p_current_model->setModel(tmp_model);
    this->p_current_model->update();
}
