#include "TopBar.h"


TopBar::TopBar
(
    QSize* _pos,
    QSize* _size,
    QWidget* _parent
) :
    QWidget(_parent),
    pos{_pos},
    size{_size}
{
    // setup label
    this->p_curr_tname = new QLabel();
    this->p_curr_tname->setPalette(QPalette(Qt::black, Qt::white));
    this->p_curr_tname->setTextFormat(Qt::MarkdownText);

    // setup buttons
    this->p_add_new_row = new QPushButton("Add row");
    this->p_delete_row = new QPushButton("Delete selected");

    // setup layout
    this->p_layout = new QHBoxLayout;

    this->p_layout->addWidget(this->p_curr_tname);
    this->p_layout->addWidget(this->p_add_new_row);
    this->p_layout->addWidget(this->p_delete_row);

    this->setLayout(this->p_layout);

    // setup geometry
    this->setGeometry
    (
        _pos->width(),
        _pos->height(),
        _size->width(),
        _size->height()
    );

    connect // add row button
    (
        this->p_add_new_row,
        &QPushButton::clicked,
        this,
        &TopBar::slot_add_new_row
    );

    connect
    (
        this->p_delete_row,
        &QPushButton::clicked,
        this,
        &TopBar::slot_delete_selected_row
    );
}

TopBar::~TopBar() {}

void TopBar::slot_set_tname(QString& _tname)
{
    QString buffer = "";
    QList<QString> lst = _tname.split('_');

    for
    (
        auto unit = lst.begin();
        unit < lst.end();
        ++unit
    )
    {
        buffer = buffer + *unit + " ";
    }

    QString mark_name = "";
    for
    (
        auto unit = buffer.begin();
        unit < buffer.end()-1;
        ++unit
    )
    {
        mark_name.push_back(*unit);
    }

    this->p_curr_tname->setText("***"+mark_name.toUpper()+"***");
}


void TopBar::slot_add_new_row()
{
    emit this->sig_add_new_row();
}

void TopBar::slot_delete_selected_row()
{
    emit this->sig_delete_selected_row();
}
