#include "InputArea.h"

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
