
#include "../includes.h"
#include "CustomButton.h"

CustomButton::CustomButton
(
    EMITS_BTN_SIGNALS _btn_sig,
    QString& _ico_path
    // QString& _btn_text
) :
    QPushButton(), btn_sig(_btn_sig)
{
    // set image
    if(_ico_path != "")
    {
        this->ico_obj = new QPixmap(_ico_path);
        this->setIcon(*(this->ico_obj));
        this->setIconSize(QSize(50, 50));
    }
    else
        this->ico_obj = nullptr;

    // if(_btn_text != "")
    //     this->btn_text = _btn_text;

    this->setMouseTracking(true); // for draw gray highlight
    this->setCheckable(true); // for draw gray/black highlight
    this->setCursor(Qt::PointingHandCursor);

    connect
    (
        this,
        &QPushButton::clicked,
        this,
        &CustomButton::checked/*emit EMITS_BTN_SIGNALS::<signal>*/
    );
}

CustomButton::~CustomButton()
{
    delete this->ico_obj;
}

inline QPixmap* CustomButton::get_ico_obj()
{
    return this->ico_obj;
}

void CustomButton::set_ico_obj(QPixmap* _px_map)
{
    delete this->ico_obj;
    this->ico_obj = _px_map;
}

EMITS_BTN_SIGNALS CustomButton::get_emitted_sig()
{
    return this->btn_sig;
}

void CustomButton::checked()
{
    emit this->is_be_checked(this->btn_sig);
}

// =========

AugmentButton::AugmentButton
(
    EMITS_BTN_SIGNALS _btn_sig,
    QString& _btn_txt
) : btn_sig(_btn_sig),
    btn_txt(_btn_txt)
{
    connect
    (
        this,
        &QPushButton::clicked,
        this,
        &AugmentButton::checked
    );
}

AugmentButton::~AugmentButton() {}

void AugmentButton::checked()
{
    emit this->is_be_checked(this->btn_sig);
}


