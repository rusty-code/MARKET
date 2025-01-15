#include "../includes.h"
#include "MenuBar.h"


MenuBar::MenuBar
(
    QSize* _size,
    QSize* _pos,
    // QPair<int, int>* _iter_buttons_cluster,
    bool _orient_layout,
    QWidget* _parent
    ) :
    QWidget(_parent),
    p_size(_size),
    p_position(_pos)
{
    // this->__iter_buttons_sigcluster = _iter_buttons_cluster;

    if(_orient_layout)
        this->p_menu_layout = new QVBoxLayout;
    else
        this->p_menu_layout = new QHBoxLayout;

    // this->p_menu_layout->addWidget(this);
    this->setLayout(this->p_menu_layout);
    this->setGeometry
    (
        _pos->width(),
        _pos->height(),
        _size->width(),
        _size->height()
    );

    this->p_items_list = new QList<CustomButton*>;
}


MenuBar::~MenuBar()
{
    delete this->p_size;
    delete this->p_position;
    delete this->p_menu_layout;
    delete this->p_items_list;
}


void MenuBar::appendObject
(
    EMITS_BTN_SIGNALS _btn_sig,
    QString _p_obj /*for rvalue arguments */
)
{
    CustomButton* tmp_object = new CustomButton(_btn_sig, _p_obj);
    this->p_menu_layout->addWidget(tmp_object);
    this->p_items_list->append(tmp_object);

    connect
    (
        tmp_object,
        &CustomButton::is_be_checked,
        this,
        &MenuBar::sig_distrib_handler
    );
}

// void MenuBar::appendObject
// (
//     EMITS_BTN_SIGNALS _btn_sig,
//     QString _btn_txt
// )
// {
//     AugmentButton* tmp_object = new AugmentButton(_btn_sig, _btn_txt);

//     // set white color on button
//     tmp_object->setPalette(QPalette(Qt::white));
//     tmp_object->setText(_btn_txt);
//     this->p_menu_layout->addWidget(tmp_object);

//     connect
//     (
//         tmp_object,
//         &AugmentButton::is_be_checked,
//         this,
//         &MenuBar::sig_distrib_handler
//     );
// }

QList<CustomButton*>* MenuBar::getObjectsList()
{
    return this->p_items_list;
}

QBoxLayout* MenuBar::get_layout()
{
    return this->p_menu_layout;
}

void MenuBar::sig_distrib_handler(EMITS_BTN_SIGNALS _clicked_btn_sig)
{
    for
    (
        int iter_btn = 0;
        iter_btn != this->p_items_list->size();
        ++iter_btn
    )
    {
        CustomButton* tmp_obj = this->p_items_list->at(iter_btn);
        if
        (
            tmp_obj->get_emitted_sig() != _clicked_btn_sig
        )
        {
            tmp_obj->setChecked(false);
        }
    }
    this->update();

    emit this->sig_transmission(_clicked_btn_sig);
}

