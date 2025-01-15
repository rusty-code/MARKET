#include "TopBar.h"


InputArea::InputArea(QString _area_txt)
{
    this->p_ledit = new QLineEdit(_area_txt);
    this->setBuddy(this->p_ledit);

    connect
    (
        this->p_ledit,
        &QLineEdit::returnPressed,
        this,
        &InputArea::slot_enter_pressed
    );
}

InputArea::~InputArea()
{}

QLineEdit* InputArea::get_edit_area()
{
    return this->p_ledit;
}

void InputArea::slot_enter_pressed()
{
    emit this->sig_get_text(this->p_ledit->text());
}

// ==============

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

    // setup other ui
    this->p_filter = new InputArea("Enter filter");
    this->p_delete_line = new InputArea("Enter delete filter");
    this->p_add_new_row = new QPushButton("Add row");

    // setup layout
    this->p_layout = new QHBoxLayout;

    this->p_layout->addWidget(this->p_curr_tname);

    this->p_layout->addWidget(this->p_filter);
    this->p_layout->addWidget(this->p_filter->get_edit_area());

    this->p_layout->addWidget(this->p_delete_line);
    this->p_layout->addWidget(this->p_delete_line->get_edit_area());

    this->p_layout->addWidget(this->p_add_new_row);

    this->setLayout(this->p_layout);

    // setup geometry
    this->setGeometry
    (
        _pos->width(),
        _pos->height(),
        _size->width(),
        _size->height()
    );

    connect // filter
    (
        this->p_filter,
        &InputArea::sig_get_text,
        this,
        &TopBar::slot_filter_transmitter
    );

    connect
    (
        this->p_delete_line,
        &InputArea::sig_get_text,
        this,
        &TopBar::slot_delete_rownum_transmitter
    );

    connect
    (
        this->p_add_new_row,
        &QPushButton::clicked,
        this,
        &TopBar::slot_add_new_row
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

void TopBar::slot_filter_transmitter(const QString& _filter)
{
    emit this->sig_filter_data_transmitter(_filter);
}

void TopBar::slot_delete_rownum_transmitter(const QString& _rownum)
{
    emit this->sig_delete_rownum_transmitter(_rownum);
}

void TopBar::slot_add_new_row()
{
    emit this->sig_add_new_row();
}
